#include <ipc-benchmark/boost/branch/performance.h>
#include <ipc-benchmark/boost/branch/types.h>
#include <list>

#define __CLASS__ "[Performance]"

using namespace std::chrono_literals;

namespace ipc_benchmark::branch {
	Performance::Performance() : ipc_benchmark::Performance() {
		logger.trace(__CLASS__, __FUNCTION__);
	}

	Performance::~Performance() {
		logger.trace(__CLASS__, __FUNCTION__);
	}

	std::chrono::nanoseconds Performance::run(uint64_t count) const {
		logger.trace(__CLASS__, __FUNCTION__, count);

		// step 1. create shared memory, mutex, and condition
		std::list<Proxy> proxies;
		for (uint64_t idx = 0; idx < count; idx++) {
			std::string strIdx = std::to_string(idx);
			const uint64_t shmsize = (10 * 1024 * 1024); // 10MB

			Proxy proxy = {{
				"Branch" + strIdx,
				"BranchTopic" + strIdx,
				"BranchMutex" + strIdx,
				"BranchCond" + strIdx,
				idx
			}, nullptr};
			
			boost::interprocess::shared_memory_object::remove(proxy.name.shm.c_str());
			Object* obj = new Object();
			obj->segment = boost::interprocess::managed_shared_memory(boost::interprocess::create_only, proxy.name.shm.c_str(), shmsize);
			obj->mutex = obj->segment.construct<boost::interprocess::interprocess_mutex>(proxy.name.mutex.c_str())();
			obj->cond = obj->segment.construct<boost::interprocess::interprocess_condition>(proxy.name.cond.c_str())();
			obj->list = new ShmStringList(obj->segment.get_segment_manager());
			obj->map = obj->segment.construct<SharedMap>(proxy.name.topic.c_str())(KeyCompare(), obj->segment.get_segment_manager());
			obj->map->insert(ValueType(idx, *(obj->list)));

			proxy.obj = obj;
			proxies.push_back(proxy);
		}

		// step 2. create communication objects
		Publisher* publisher = nullptr;
		std::list<Subscriber*> subscribers;

		// step 2.1. create publisher
		publisher = new Publisher(proxies);
		if (publisher == nullptr) {
			// ERROR
			return 0ns;
		}

		// step 2.2. create subscribers
		for (Proxy& proxy: proxies) {
			subscribers.push_back(new Subscriber(proxy.name));
		}

		// step 3. ready
		// step 3.1. ready publisher
		if (publisher->ready() == false) {
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

		// step 5. release resources
		delete(publisher);
		for (Subscriber* subscriber : subscribers) {
			delete(subscriber);
		}
		subscribers.clear();
		
		for (Proxy& proxy: proxies) {
			proxy.obj->segment.destroy<boost::interprocess::interprocess_condition>(proxy.name.cond.c_str());
			proxy.obj->segment.destroy<boost::interprocess::interprocess_mutex>(proxy.name.mutex.c_str());
			proxy.obj->segment.destroy<SharedMap>(proxy.name.topic.c_str());
			boost::interprocess::shared_memory_object::remove(proxy.name.shm.c_str());
		}

		return result;
	}
}
