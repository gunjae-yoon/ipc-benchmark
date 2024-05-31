#include <ipc-benchmark/version.h>
#include <ipc-benchmark/base/performance.h>
#include <ipc-benchmark/boost/branch/performance.h>
#include <ipc-benchmark/boost/trunk/performance.h>
#include <ipc-benchmark/posix/mqueue/performance.h>
#include <boost/core/demangle.hpp>
#include <iostream>
#include <typeinfo>
#include <sstream>
#include <locale>
#include <iomanip>

using namespace ipc_benchmark;

struct comma_facet : public std::numpunct<char> {
protected:
    virtual char do_thousands_sep() const override { return ','; }
    virtual std::string do_grouping() const override { return "\3"; }
};

int main(int argc, char** argv) {
	logger.info("ipc-benchmark version:", Version::full);
	const uint64_t count = 100;
	const Performance* tests[] = { new branch::Performance(), new trunk::Performance(), new mqueue::Performance() };

	for (const Performance* test : tests) {
		uint64_t value = test->run(count).count();
		std::stringstream ss;
		ss.imbue(std::locale(std::locale::classic(), new comma_facet));
		ss << value;
		logger.info("test result of", boost::core::demangle(typeid(*test).name()), "is", ss.str(), "nanoseconds");
	}
	return 0;
}
