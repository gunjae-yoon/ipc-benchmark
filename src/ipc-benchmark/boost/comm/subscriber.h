#ifndef __ipc_benchmark_boost_comm_subscirber_h__
#define __ipc_benchmark_boost_comm_subscirber_h__

#include <ipc-benchmark/boost/base/types.h>
#include <cstdint>
#include <string>

namespace ipc_benchmark {
	class Subscriber {
	public:
		Subscriber(std::string shmname, std::string topicname, uint64_t idx);
		~Subscriber();
		
		bool ready();
		void run();
	};
}

#endif
