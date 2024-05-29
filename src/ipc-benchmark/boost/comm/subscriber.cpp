#include <ipc-benchmark/boost/comm/subscriber.h>

namespace ipc_benchmark {
	Subscriber::Subscriber(std::string shmname, std::string topicname) {
	}

	Subscriber::~Subscriber() {
	}

	bool Subscriber::ready() {
		return true;
	}

	void Subscriber::run() {
	}
}
