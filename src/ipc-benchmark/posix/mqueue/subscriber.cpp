#include <ipc-benchmark/posix/mqueue/subscriber.h>
#include <ipc-benchmark/base/performance.h>

namespace ipc_benchmark::mqueue {
	Subscriber::Subscriber(std::string topicname) : topic(topicname), desc(-1), thread(nullptr), buffer({MqString::BUF_LEN, new char[MqString::BUF_LEN]}) {
	}

	Subscriber::~Subscriber() {
		if ((thread != nullptr) && (thread->joinable())) {
			thread->join();
		}
		delete(thread);
		thread = nullptr;

		if (buffer.mem != nullptr) {
			delete[](buffer.mem);
		}
		
		if (desc != -1) {
			mq_close(desc);
		}
	}

	bool Subscriber::ready() {
		desc = mq_open(topic.c_str(), O_RDWR);
		if (desc == -1) {
			return false;
		}

		thread = new std::thread([&](){
			uint64_t received = 0;
			MqString data;
			while (received < Performance::DATA_AMOUNT) {
				if (mq_receive(desc, buffer.mem, MqString::BUF_LEN, 0) == -1) {
					break;
				}
				data.deserialize(buffer.mem);
				received++;
			}
		});

		return true;
	}

	void Subscriber::run() {
	}

	void Subscriber::wait() {
		if ((thread != nullptr) && (thread->joinable())) {
			thread->join();
		}
	}
}
