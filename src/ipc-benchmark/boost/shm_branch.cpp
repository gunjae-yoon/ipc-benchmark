#include <ipc-benchmark/boost/shm_branch.h>

#define __CLASS__ "[ShmBranch]"

using namespace std::chrono_literals;

namespace ipc_benchmark {
	ShmBranch::ShmBranch() : Performance() {
		logger.trace(__CLASS__, __FUNCTION__);
	}

	ShmBranch::~ShmBranch() {
		logger.trace(__CLASS__, __FUNCTION__);
	}

	std::chrono::nanoseconds ShmBranch::run(uint64_t count) const {
		logger.trace(__CLASS__, __FUNCTION__, count);
		return 0ns;
	}
}
