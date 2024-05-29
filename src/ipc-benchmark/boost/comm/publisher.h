#ifndef __ipc_benchmark_boost_comm_publisher_h__
#define __ipc_benchmark_boost_comm_publisher_h__

#include <ipc-benchmark/boost/base/types.h>
#include <cstdint>
#include <string>

namespace ipc_benchmark {
	class Publisher {
	public:
		Publisher(std::string shmname, std::string topicname);
		~Publisher();
		
		bool ready();
		void run();
	};
}

#endif
