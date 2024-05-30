#ifndef __ipc_benchmark_boost_branch_types_h__
#define __ipc_benchmark_boost_branch_types_h__

#include <ipc-benchmark/boost/base/types.h>

namespace ipc_benchmark {
	namespace branch {
		struct Name {
			std::string shm;
			std::string topic;
			std::string mutex;
			std::string cond;
			uint64_t id;
		};
		
		struct Object {
			boost::interprocess::managed_shared_memory segment;
			boost::interprocess::interprocess_mutex* mutex;
			boost::interprocess::interprocess_condition* cond;
			SharedMap* map;
			ShmStringList* list;
		};
		
		struct Proxy {
			Name name;
			Object* obj;
		};
	}
}

#endif
