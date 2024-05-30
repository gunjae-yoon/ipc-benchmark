#ifndef __ipc_benchmark_boost_branch_subscirber_h__
#define __ipc_benchmark_boost_branch_subscriber_h__

#include <ipc-benchmark/boost/base/types.h>
#include <ipc-benchmark/boost/branch/types.h>
#include <cstdint>
#include <string>
#include <thread>

namespace ipc_benchmark {
	namespace branch {
		class Subscriber {
		public:
			Subscriber(Name nameSet);
			~Subscriber();
			
			bool ready();
			void run();
			void wait();
		
		private:
			Name name;
			Object obj;
			std::thread* thread;
		};
	}
}

#endif
