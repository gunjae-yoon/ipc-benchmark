#include <ipc-benchmark/boost/comm/publisher.h>

namespace ipc_benchmark {
	Publisher::Publisher(std::string shmname, std::string topicname) {
	}

	Publisher::~Publisher() {
	}

	bool Publisher::ready() {
		return true;
	}

	void Publisher::run() {
	}
}
