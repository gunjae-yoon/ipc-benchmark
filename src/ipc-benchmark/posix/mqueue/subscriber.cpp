#include <ipc-benchmark/posix/mqueue/subscriber.h>

namespace ipc_benchmark::mqueue {
	Subscriber::Subscriber(std::string topicname) : topic(topicname), desc(), thread(nullptr), buffer({MqString::BUF_LEN, new char[MqString::BUF_LEN]}) {
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
