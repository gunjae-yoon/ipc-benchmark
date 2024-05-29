#include <ipc-benchmark/boost/comm/subscriber.h>

namespace ipc_benchmark {
	Subscriber::Subscriber(std::string shmname, std::string topicname, std::uint64_t idx) {
	}

	Subscriber::~Subscriber() {
	}

	bool Subscriber::ready() {
		return true;
	}

	void Subscriber::run() {
	}
}
