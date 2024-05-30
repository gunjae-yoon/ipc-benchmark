#include <ipc-benchmark/boost/branch/publisher.h>
#include <ipc-benchmark/base/performance.h>
#include <guutil/log/logger.h>

namespace ipc_benchmark::branch {
	extern guutil::log::Logger logger; // global logger

	Publisher::Publisher(std::string shmname, std::string topicname, uint64_t subscribers) {
	}

	Publisher::~Publisher() {
	}

	bool Publisher::ready() {
		return true;
	}

	void Publisher::run() {
	}
}
