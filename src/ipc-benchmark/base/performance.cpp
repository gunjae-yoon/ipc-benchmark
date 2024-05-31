#include <ipc-benchmark/base/performance.h>

namespace ipc_benchmark {
	guutil::log::Logger logger("global", guutil::log::Level::INFO, guutil::log::Target::ALL);
	
	const uint64_t Performance::DATA_AMOUNT = 10000;
}
