#ifndef __ipc_benchmark_boost_branch_publisher_h__
#define __ipc_benchmark_boost_branch_publisher_h__

#include <ipc-benchmark/boost/base/types.h>
#include <cstdint>
#include <string>

namespace ipc_benchmark {
	namespace branch {
		class Publisher {
		public:
			Publisher(std::string shmname, std::string topicname, uint64_t subscribers);
			~Publisher();
			
			bool ready();
			void run();
		};
	}
}

#endif
