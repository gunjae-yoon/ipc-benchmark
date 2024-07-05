#include <ipc-benchmark/base/performance.h>

#ifndef TEST_DATA_AMOUNT
#define TEST_DATA_AMOUNT 10000
#endif

namespace ipc_benchmark {
	guutil::log::Logger logger("global", guutil::log::Level::INFO, guutil::log::Target::ALL);
	
	const uint64_t Performance::DATA_AMOUNT = TEST_DATA_AMOUNT;
}
