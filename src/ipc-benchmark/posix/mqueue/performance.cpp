#include <ipc-benchmark/posix/mqueue/performance.h>
#include <list>

#define __CLASS__ "[Performance]"

using namespace std::chrono_literals;

namespace ipc_benchmark::mqueue {
	Performance::Performance() : ipc_benchmark::Performance() {
	}

	Performance::~Performance() {
	}

	std::chrono::nanoseconds Performance::run(uint64_t count) const {
		std::chrono::time_point begin = std::chrono::system_clock::now();
		std::chrono::time_point end = std::chrono::system_clock::now();
		std::chrono::nanoseconds result = (end - begin);
		
		return result;
	}
}
