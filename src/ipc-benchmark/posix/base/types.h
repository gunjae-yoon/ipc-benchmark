#ifndef __ipc_benchmark_posix_base_types_h__
#define __ipc_benchmark_posix_base_types_h__

#include <string>
#include <mqueue.h>

namespace ipc_benchmark {
	namespace mqueue {
		struct Proxy{
			std::string topic;
			mqd_t desc;
		};
	}
}

#endif
