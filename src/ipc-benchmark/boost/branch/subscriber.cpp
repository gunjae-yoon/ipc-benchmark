#include <ipc-benchmark/boost/branch/subscriber.h>
#include <ipc-benchmark/base/performance.h>
#include <guutil/log/logger.h>

namespace ipc_benchmark::branch {
	extern guutil::log::Logger logger; // global logger

	Subscriber::Subscriber(std::string shmname, std::string topicname, uint64_t idx) {
	}

	Subscriber::~Subscriber() {
	}

	bool Subscriber::ready() {
		return true;
	}

	void Subscriber::run() {
	}

	void Subscriber::wait() {
	}
}
