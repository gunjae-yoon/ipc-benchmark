#ifndef __ipc_benchmark_posix_mqueue_subscriber_h__
#define __ipc_benchmark_posix_mqueue_subscriber_h__

#include <ipc-benchmark/posix/base/mqstring.h>
#include <ipc-benchmark/posix/base/types.h>
#include <list>
#include <thread>

namespace ipc_benchmark {
	namespace mqueue {
		class Subscriber {
		public:
			Subscriber(std::string topicname);
			~Subscriber();
			
			bool ready();
			void run();
			void wait();
			
		private:
			std::string topic;
			mqd_t desc;
			std::thread* thread;
		};
	}
}

#endif
