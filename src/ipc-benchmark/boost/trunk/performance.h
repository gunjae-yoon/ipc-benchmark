#ifndef __ipc_benchmark_boost_trunk_performance_h__
#define __ipc_benchmark_boost_trunk_performance_h__

#include <ipc-benchmark/base/performance.h>
#include <ipc-benchmark/boost/trunk/publisher.h>
#include <ipc-benchmark/boost/trunk/subscriber.h>

namespace ipc_benchmark {
	namespace trunk {
		class Performance : public ipc_benchmark::Performance {
		public:
			Performance();
			~Performance();
		
			std::chrono::nanoseconds run(uint64_t count) const override;
		};
	}
}

#endif
