#include <ipc-benchmark/boost/branch/publisher.h>
#include <ipc-benchmark/base/performance.h>
#include <guutil/log/logger.h>

namespace ipc_benchmark::branch {
	extern guutil::log::Logger logger; // global logger

	Publisher::Publisher(std::list<Proxy>& targets) {
		for (Proxy& target : targets) {
			proxies.push_back({target.name, nullptr});
		}
	}

	Publisher::~Publisher() {
	}

	bool Publisher::ready() {
		return true;
	}

	void Publisher::run() {
	}
}
