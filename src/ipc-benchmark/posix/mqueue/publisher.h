#ifndef __ipc_benchmark_posix_mqueue_publisher_h__
#define __ipc_benchmark_posix_mqueue_publisher_h__

#include <ipc-benchmark/posix/base/mqstring.h>
#include <ipc-benchmark/posix/base/types.h>
#include <list>

namespace ipc_benchmark {
	namespace mqueue {
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
