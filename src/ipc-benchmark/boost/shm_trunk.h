#ifndef __ipc_benchmark_boost_shm_trunk_h__
#define __ipc_benchmark_boost_shm_trunk_h__

#include <ipc-benchmark/base/performance.h>

namespace ipc_benchmark {
	class ShmTrunk : public Performance {
	public:
		ShmTrunk();
		~ShmTrunk();

		std::chrono::nanoseconds run(uint64_t count) const override;
	};
}

#endif
