#include <ipc-benchmark/version.h>
#include <iostream>

using namespace ipc_benchmark;

int main(int argc, char** argv) {
	std::cout << "ipc-benchmark version: " << Version::full << std::endl;
	return 0;
}
