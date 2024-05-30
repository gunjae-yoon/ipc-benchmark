#include <ipc-benchmark/posix/mqueue/publisher.h>

namespace ipc_benchmark::mqueue {
	Publisher::Publisher(std::list<Proxy>& targets) {
		for (Proxy& target : targets) {
			proxies.push_back({target.topic, {}});
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
