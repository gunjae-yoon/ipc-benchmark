#include <ipc-benchmark/boost/shm_trunk.h>

#define __CLASS__ "[ShmTrunk]"

using namespace std::chrono_literals;

namespace ipc_benchmark {
	ShmTrunk::ShmTrunk() : Performance() {
		logger.trace(__CLASS__, __FUNCTION__);
	}

	ShmTrunk::~ShmTrunk() {
		logger.trace(__CLASS__, __FUNCTION__);
	}

	std::chrono::nanoseconds ShmTrunk::run(uint64_t count) const {
		logger.trace(__CLASS__, __FUNCTION__, count);
		return 0ns;
	}
}
