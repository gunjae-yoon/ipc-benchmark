#include <ipc-benchmark/boost/comm/publisher.h>

namespace ipc_benchmark {
	Publisher::Publisher(std::string shmname, std::string topicname, uint64_t subscribers) {
		name.shm = shmname;
		name.topic = topicname;
		count = subscribers;
	}

	Publisher::~Publisher() {
	}

	bool Publisher::ready() {
		segment = boost::interprocess::managed_shared_memory(boost::interprocess::open_only, name.shm.c_str());
		return true;
	}

	void Publisher::run() {
	}
}
