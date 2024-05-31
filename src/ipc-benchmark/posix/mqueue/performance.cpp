#include <ipc-benchmark/posix/mqueue/performance.h>
#include <list>

#define __CLASS__ "[Performance]"

using namespace std::chrono_literals;

namespace ipc_benchmark::mqueue {
	Performance::Performance() : ipc_benchmark::Performance() {
	}

	Performance::~Performance() {
	}

	std::chrono::nanoseconds Performance::run(uint64_t count) const {
		// step 1. create message queue
		std::list<Proxy> proxies;
		for (uint64_t idx = 0; idx < count; idx++) {
			struct mq_attr mqAttr = {}; 
            mqAttr.mq_flags = 0; // blocking mode (0) | non-blocking mode (O_NONBLOCK)
            mqAttr.mq_maxmsg = 10; // Note. depends on the value of "/proc/sys/fs/mqueue/msg_max"
            mqAttr.mq_msgsize = MqString::BUF_LEN;

			Proxy proxy = {"/PosixMqueue" + std::to_string(idx), -1};
			proxy.desc = mq_open(proxy.topic.c_str(), O_RDWR | O_CREAT, 0666, &mqAttr);
			if (proxy.desc == -1) {
				return 0ns;
			}
			
			proxies.push_back(proxy);
		}

		// step 2. create communication objects
		Publisher* publisher = nullptr;
		std::list<Subscriber*> subscribers;

		// step 2.1. create publisher
		publisher = new Publisher(proxies);
		if (publisher == nullptr) {
			// ERROR
			return 0ns;
		}

		// step 2.2. create subscribers
		for (Proxy& proxy: proxies) {
			subscribers.push_back(new Subscriber(proxy.topic));
		}

		// step 3. ready
		// step 3.1. ready publisher
		if (publisher->ready() == false) {
			return 0ns;
		}

		// step 3.2. ready subscriber
		for (Subscriber* subscriber : subscribers) {
			if (subscriber->ready() == false) {
				// ERROR
				return 0ns;
			}
		}

		// step 4. run
		std::chrono::time_point begin = std::chrono::system_clock::now();
		publisher->run();
		for (Subscriber* subscriber : subscribers) {
			subscriber->wait();
		}
		std::chrono::time_point end = std::chrono::system_clock::now();
		std::chrono::nanoseconds result = (end - begin);

		// step 5. release resources
		delete(publisher);
		for (Subscriber* subscriber : subscribers) {
			delete(subscriber);
		}
		subscribers.clear();

		for (Proxy& proxy: proxies) {
			if (proxy.desc != -1) {
				mq_close(proxy.desc);
				mq_unlink(proxy.topic.c_str());
			}
		}
		
		return result;
	}
}
