#include <ipc-benchmark/posix/mqueue/publisher.h>
#include <ipc-benchmark/base/performance.h>

#ifndef TEST_DATA_LENGTH
#define TEST_DATA_LENGTH (size_t)(10*1024*1024)
#endif

namespace ipc_benchmark::mqueue {
	Publisher::Publisher(std::list<Proxy>& targets) {
		for (Proxy& target : targets) {
			proxies.push_back({target.topic, -1});
		}
	}

	Publisher::~Publisher() {
		for (Proxy& proxy : proxies) {
			if (proxy.desc != -1) {
				mq_close(proxy.desc);
			}
		}
	}

	bool Publisher::ready() {
		for (Proxy& proxy : proxies) {
			proxy.desc = mq_open(proxy.topic.c_str(), O_RDWR);
			if (proxy.desc == -1) {
				return false;
			}
		}

		return true;
	}

	void Publisher::run() {
		char* buffer = new char[MqString::BUF_LEN];
		if (buffer == nullptr) {
			return;
		}
		
		MqString data;
		char pattern = '0';
		uint64_t published = 0;
		while (published < Performance::DATA_AMOUNT) {
			data.value = std::string(TEST_DATA_LENGTH, pattern + (published % 10));
			data.serialize(buffer, MqString::BUF_LEN);
			for (Proxy& proxy: proxies) {
				if (mq_send(proxy.desc, buffer, MqString::BUF_LEN, 0) == -1) {
					// failed to send message
				}
			}
			published++;
		}

		delete[](buffer);
	}
}
