#include <ipc-benchmark/boost/comm/publisher.h>

namespace ipc_benchmark {
	Publisher::Publisher(std::string shmname, std::string topicname, uint64_t subscribers) {
		name.shm = shmname;
		name.topic = topicname;
		count = subscribers;
		targets.resize(count, {nullptr, nullptr});
	}

	Publisher::~Publisher() {
	}

	bool Publisher::ready() {
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

		for (uint64_t idx = 0; idx < count; idx++) {
			const std::string shmcond = "TrunkCondition" + std::to_string(idx);
			targets[idx].cond = segment.find<boost::interprocess::interprocess_condition>(shmcond.c_str()).first;
			targets[idx].vector = &shmmap->find(idx)->second;
			if ((targets[idx].cond == nullptr) || (targets[idx].vector == nullptr)) {
				return false;
			}
		}
		return true;
	}

	void Publisher::run() {
	}
}
