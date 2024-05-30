#ifndef __ipc_benchmark_posix_mqueue_performance_h__
#define __ipc_benchmark_posix_mqueue_performance_h__

#include <ipc-benchmark/base/performance.h>
#include <ipc-benchmark/posix/mqueue/publisher.h>
#include <ipc-benchmark/posix/mqueue/subscriber.h>

namespace ipc_benchmark {
	namespace mqueue {
		class Performance : public ipc_benchmark::Performance {
		public:
			Performance();
			~Performance();
		
			std::chrono::nanoseconds run(uint64_t count) const override;
		};
	}
}

#endif
