#ifndef __ipc_benchmark_boost_branch_publisher_h__
#define __ipc_benchmark_boost_branch_publisher_h__

#include <ipc-benchmark/boost/base/types.h>
#include <ipc-benchmark/boost/branch/types.h>
#include <cstdint>
#include <string>
#include <list>

namespace ipc_benchmark {
	namespace branch {
		class Publisher {
		public:
			Publisher(std::list<Proxy>& targets);
			~Publisher();
			
			bool ready();
			void run();
			
		private:
			std::list<Proxy> proxies;
		};
	}
}

#endif
