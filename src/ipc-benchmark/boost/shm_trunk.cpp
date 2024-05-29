#include <ipc-benchmark/boost/shm_trunk.h>

using namespace std::chrono_literals;

namespace ipc_benchmark {
	ShmTrunk::ShmTrunk() : Performance() {
	}

	ShmTrunk::~ShmTrunk() {
	}

	std::chrono::nanoseconds ShmTrunk::run(uint64_t count) const {
		return 0ns;
	}
}
