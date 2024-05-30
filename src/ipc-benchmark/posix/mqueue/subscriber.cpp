#include <ipc-benchmark/posix/mqueue/subscriber.h>

namespace ipc_benchmark::mqueue {
	Subscriber::Subscriber(std::string topicname) : topic(topicname), desc(), thread(nullptr) {
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
