#include <ipc-benchmark/boost/trunk/subscriber.h>
#include <ipc-benchmark/base/performance.h>
#include <guutil/log/logger.h>

namespace ipc_benchmark::trunk {
	extern guutil::log::Logger logger; // global logger

	Subscriber::Subscriber(std::string shmname, std::string topicname, std::uint64_t idx) {
		name.shm = shmname;
		name.topic = topicname;
		id = idx;
		thread = nullptr;
	}

	Subscriber::~Subscriber() {
		if ((thread != nullptr) && (thread->joinable())) {
			thread->join();
		}
		delete(thread);
		thread = nullptr;
	}

	bool Subscriber::ready() {
		segment = boost::interprocess::managed_shared_memory(boost::interprocess::open_only, name.shm.c_str());
		
		// TODO: need to make flexibly
		mutex = segment.find<boost::interprocess::interprocess_mutex>("TrunkMutex").first;
		if (mutex == nullptr) {
			return false;
		}

		SharedMap* shmmap = segment.find<SharedMap>(name.topic.c_str()).first;
		if (shmmap == nullptr) {
			return false;;
		}

		const std::string shmcond = "TrunkCondition" + std::to_string(id);
		cond = segment.find<boost::interprocess::interprocess_condition>(shmcond.c_str()).first;
		list = &shmmap->find(id)->second;
		if ((cond == nullptr) || (list == nullptr)) {
			return false;
		}

		thread = new std::thread([&](){
			uint64_t received = 0;
			// TODO: need to make flexibly
			while (received < Performance::DATA_AMOUNT) {
				boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(*mutex);
				while (list->empty() == false) {
					received++;
					list->pop_front();
				}
				if (received < Performance::DATA_AMOUNT) {
					cond->wait(lock);
				}
			}
		});

		if (thread == nullptr) {
			return false;
		}

		return true;
	}

	void Subscriber::run() {
	}

	void Subscriber::wait() {
		if ((thread != nullptr) && (thread->joinable())) {
			thread->join();
		}
	}
}
