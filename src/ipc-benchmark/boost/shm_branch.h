#ifndef __ipc_benchmark_boost_shm_branch_h__
#define __ipc_benchmark_boost_shm_branch_h__

#include <ipc-benchmark/base/performance.h>

namespace ipc_benchmark {
	class ShmBranch : public Performance {
	public:
		ShmBranch();
		~ShmBranch();

		std::chrono::nanoseconds run(uint64_t count) const override;
	};
}

#endif
