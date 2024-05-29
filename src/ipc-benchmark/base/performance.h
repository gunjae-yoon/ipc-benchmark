#ifndef __ipc_benchmark_base_performance_h__
#define __ipc_benchmark_base_performance_h__

#include <cstdint>
#include <chrono>
#include <guutil/log/logger.h>

namespace ipc_benchmark {
	class Performance {
	public:
		Performance() = default;
		virtual ~Performance() = default;
		
		virtual std::chrono::nanoseconds run(uint64_t count) const = 0;
	};

	extern guutil::log::Logger logger; // global logger
}

#endif
