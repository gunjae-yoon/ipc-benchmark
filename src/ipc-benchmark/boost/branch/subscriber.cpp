#include <ipc-benchmark/boost/branch/subscriber.h>
#include <ipc-benchmark/base/performance.h>
#include <guutil/log/logger.h>

namespace ipc_benchmark::branch {
	extern guutil::log::Logger logger; // global logger

	Subscriber::Subscriber(Name nameSet) : name(nameSet), thread(nullptr) {
	}

	Subscriber::~Subscriber() {
		if ((thread != nullptr) && (thread->joinable())) {
			thread->join();
		}
		delete(thread);
		thread = nullptr;
	}

	bool Subscriber::ready() {
		obj.segment = boost::interprocess::managed_shared_memory(boost::interprocess::open_only, name.shm.c_str());
		obj.mutex = obj.segment.find<boost::interprocess::interprocess_mutex>(name.mutex.c_str()).first;
		obj.cond = obj.segment.find<boost::interprocess::interprocess_condition>(name.cond.c_str()).first;
		obj.map = obj.segment.find<SharedMap>(name.topic.c_str()).first;
		obj.list = &(obj.map->find(name.id)->second);

		thread = new std::thread([&](){
			uint64_t received = 0;
			while (received < Performance::DATA_AMOUNT) {
				boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(*(obj.mutex));
				while (obj.list->empty() == false) {
					received++;
					obj.list->pop_front();
				}
				if (received < Performance::DATA_AMOUNT) {
					obj.cond->wait(lock);
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
