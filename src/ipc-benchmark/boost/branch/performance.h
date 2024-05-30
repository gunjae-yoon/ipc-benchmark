#ifndef __ipc_benchmark_boost_branch_performance_h__
#define __ipc_benchmark_boost_branch_performance_h__

#include <ipc-benchmark/base/performance.h>

namespace ipc_benchmark {
	namespace branch {
		class Performance : public ipc_benchmark::Performance {
		public:
			Performance();
			~Performance();
		
			std::chrono::nanoseconds run(uint64_t count) const override;
		};
	}
}

#endif
