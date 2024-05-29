#include <ipc-benchmark/boost/shm_branch.h>

using namespace std::chrono_literals;

namespace ipc_benchmark {
	ShmBranch::ShmBranch() : Performance() {
	}

	ShmBranch::~ShmBranch() {
	}

	std::chrono::nanoseconds ShmBranch::run(uint64_t count) const {
		return 0ns;
	}
}
