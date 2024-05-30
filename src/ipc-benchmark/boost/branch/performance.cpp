#include <ipc-benchmark/boost/branch/performance.h>

#define __CLASS__ "[Performance]"

using namespace std::chrono_literals;

namespace ipc_benchmark::branch {
	Performance::Performance() : ipc_benchmark::Performance() {
		logger.trace(__CLASS__, __FUNCTION__);
	}

	Performance::~Performance() {
		logger.trace(__CLASS__, __FUNCTION__);
	}

	std::chrono::nanoseconds Performance::run(uint64_t count) const {
		logger.trace(__CLASS__, __FUNCTION__, count);
		std::chrono::time_point begin = std::chrono::system_clock::now();
		std::chrono::time_point end = std::chrono::system_clock::now();
		return end - begin;
	}
}
