#include <ipc-benchmark/version.h>
#include <ipc-benchmark/base/performance.h>
#include <ipc-benchmark/boost/shm_branch.h>
#include <ipc-benchmark/boost/shm_trunk.h>
#include <boost/core/demangle.hpp>
#include <iostream>
#include <typeinfo>

using namespace ipc_benchmark;

int main(int argc, char** argv) {
	logger.info("ipc-benchmark version:", Version::full);
	const uint64_t count = 100;
	const Performance* tests[] = { new ShmBranch(), new ShmTrunk() };

	for (const Performance* test : tests) {
		logger.info("test result of", boost::core::demangle(typeid(*test).name()), "is", test->run(count).count(), "nanoseconds");
	}
	return 0;
}
