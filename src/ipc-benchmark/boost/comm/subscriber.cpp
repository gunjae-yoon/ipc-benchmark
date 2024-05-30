#include <ipc-benchmark/boost/comm/subscriber.h>
#include <thread>

namespace ipc_benchmark {
	Subscriber::Subscriber(std::string shmname, std::string topicname, std::uint64_t idx) {
		name.shm = shmname;
		name.topic = topicname;
		id = idx;
	}

	Subscriber::~Subscriber() {
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

		return true;
	}

	void Subscriber::run() {
	}
}
