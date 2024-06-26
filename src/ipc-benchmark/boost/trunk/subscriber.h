#ifndef __ipc_benchmark_boost_trunk_subscirber_h__
#define __ipc_benchmark_boost_trunk_subscirber_h__

#include <ipc-benchmark/boost/base/types.h>
#include <cstdint>
#include <string>
#include <thread>

namespace ipc_benchmark {
	namespace trunk {
		class Subscriber {
		public:
			Subscriber(std::string shmname, std::string topicname, uint64_t idx);
			~Subscriber();
			
			bool ready();
			void run();
			void wait();
		
		private:
			struct {
				std::string shm;
				std::string topic;
			} name;
			uint64_t id;
			boost::interprocess::managed_shared_memory segment;
			boost::interprocess::interprocess_mutex* mutex;
			boost::interprocess::interprocess_condition* cond;
			ShmStringList* list;
			std::thread* thread;
		};
	}
}

#endif
