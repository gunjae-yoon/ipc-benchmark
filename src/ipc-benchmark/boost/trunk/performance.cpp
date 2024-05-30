#include <ipc-benchmark/boost/trunk/performance.h>
#include <list>

#define __CLASS__ "[Performance]"

using namespace std::chrono_literals;

namespace ipc_benchmark::trunk {
	Performance::Performance() : ipc_benchmark::Performance() {
		logger.trace(__CLASS__, __FUNCTION__);
	}

	Performance::~Performance() {
		logger.trace(__CLASS__, __FUNCTION__);
	}

	std::chrono::nanoseconds Performance::run(uint64_t count) const {
		logger.trace(__CLASS__, __FUNCTION__, count);

		// step 1. create shared memory, mutex, and condition
		const char* shmname = "Trunk";
		const char* topicname = "TrunkTopic";
		const char* shmmutex = "TrunkMutex";
		const uint64_t shmsize = (500 * 1024 * 1024); // 500MB
		
		boost::interprocess::shared_memory_object::remove(shmname);
		boost::interprocess::managed_shared_memory segment(boost::interprocess::create_only, shmname, shmsize);
		const ShmAllocator alloc(segment.get_segment_manager());

		SharedMap* shmmap = segment.construct<SharedMap>(topicname)(KeyCompare(), alloc);
		boost::interprocess::interprocess_mutex* mutex = segment.construct<boost::interprocess::interprocess_mutex>(shmmutex)();
		std::list<boost::interprocess::interprocess_condition*> cond;
		std::list<ShmStringList*> shmlist;
		for (uint64_t idx = 0; idx < count; idx++) {
			const std::string shmcond = "TrunkCondition" + std::to_string(idx);
			cond.push_back(segment.construct<boost::interprocess::interprocess_condition>(shmcond.c_str())());
			ShmStringList* list = new ShmStringList(alloc);
			shmlist.push_back(list);
			shmmap->insert(ValueType(idx, *list));
		}
		
		// step 2. create communication objects
		Publisher* publisher = nullptr;
		std::list<Subscriber*> subscribers;
		
		// step 2.1. create publisher
		publisher = new Publisher(shmname, topicname, count);
		if (publisher == nullptr) {
			// ERROR
			return 0ns;
		}

		// step 2.2. create subscribers
		for (uint64_t idx = 0; idx < count; idx++) {
			Subscriber* subscriber = new Subscriber(shmname, topicname, idx);
			if (subscriber == nullptr) {
				// ERROR
				return 0ns;
			}
			subscribers.push_back(subscriber);
		}

		// step 3. ready
		// step 3.1. ready publisher
		if (publisher->ready() == false) {
			// ERROR
			return 0ns;
		}

		// step 3.2. ready subscriber
		for (Subscriber* subscriber : subscribers) {
			if (subscriber->ready() == false) {
				// ERROR
				return 0ns;
			}
		}
		
		// step 4. run
		std::chrono::time_point begin = std::chrono::system_clock::now();
		publisher->run();
		for (Subscriber* subscriber : subscribers) {
			subscriber->wait();
		}
		std::chrono::time_point end = std::chrono::system_clock::now();
		std::chrono::nanoseconds result = (end - begin);
		logger.debug(__CLASS__, __FUNCTION__, "waiting was done");
		
		// step 5. release resources
		delete(publisher);
		for (Subscriber* subscriber : subscribers) {
			delete(subscriber);
		}
		subscribers.clear();
		
		for (uint64_t idx = 0; idx < count; idx++) {
			const std::string shmcond = "TrunkCondition" + std::to_string(idx);
			segment.destroy<boost::interprocess::interprocess_condition>(shmcond.c_str());
		}
		segment.destroy<boost::interprocess::interprocess_mutex>(shmmutex);
		segment.destroy<SharedMap>(topicname);
		boost::interprocess::shared_memory_object::remove(shmname);

		return result;
	}
}
