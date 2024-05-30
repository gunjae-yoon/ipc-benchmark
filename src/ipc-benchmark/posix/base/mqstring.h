#ifndef __ipc_benchmark_posix_base_mqstring_h__
#define __ipc_benchmark_posix_base_mqstring_h__

#include <cstdint>
#include <string>

namespace ipc_benchmark {
	class MqString {
	public:
		static const uint64_t MAX_LEN;
		static const uint64_t BUF_LEN;
	
	public:
		MqString(std::string val = "");
		~MqString();

		void serialize(char* buffer, uint64_t capacity);
		void deserialize(char* buffer);
	
	public:
		std::string value;
	};
}

#endif
