#include <ipc-benchmark/boost/branch/subscriber.h>
#include <ipc-benchmark/base/performance.h>
#include <guutil/log/logger.h>

namespace ipc_benchmark::branch {
	extern guutil::log::Logger logger; // global logger

	Subscriber::Subscriber(Name nameSet) : name(nameSet), obj(nullptr) {
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
