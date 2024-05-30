#ifndef __ipc_benchmark_boost_comm_publisher_h__
#define __ipc_benchmark_boost_comm_publisher_h__

#include <ipc-benchmark/boost/base/types.h>
#include <cstdint>
#include <string>

namespace ipc_benchmark {
	class Publisher {
	public:
		Publisher(std::string shmname, std::string topicname, uint64_t subscribers);
		~Publisher();
		
		bool ready();
		void run();

	private:
		struct {
			std::string shm;
			std::string topic;
		} name;
		uint64_t count;
		boost::interprocess::managed_shared_memory segment;
		boost::interprocess::interprocess_mutex* mutex;
		struct Proxy{
			boost::interprocess::interprocess_condition* cond;
			ShmStringList* list;
		};
		std::vector<Proxy> targets;
	};
}

#endif
