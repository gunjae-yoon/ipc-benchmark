#ifndef __ipc_benchmark_base_performance_h__
#define __ipc_benchmark_base_performance_h__

#include <cstdint>
#include <chrono>

namespace ipc_benchmark {
	class Performance {
	public:
		Performance();
		virtual ~Performance();
		
		virtual std::chrono::nanoseconds run(uint64_t count) const = 0;
	};
}

#endif
