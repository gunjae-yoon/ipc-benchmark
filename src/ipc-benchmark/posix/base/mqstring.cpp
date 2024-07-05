#include <ipc-benchmark/posix/base/mqstring.h>
#include <cstdlib>

#ifndef TEST_DATA_LENGTH
#define TEST_DATA_LENGTH (size_t)(10*1024*1024)
#endif

namespace ipc_benchmark {
	const uint64_t MqString::MAX_LEN = TEST_DATA_LENGTH;
	const uint64_t MqString::BUF_LEN = (TEST_DATA_LENGTH + sizeof(uint32_t));

	MqString::MqString(std::string val) : value(val) {
	}

	MqString::~MqString() {
	}

	void MqString::serialize(char* buffer, uint64_t capacity) {
		if (capacity < value.length()) {
			return;
		}
		
		uint32_t* len = reinterpret_cast<uint32_t*>(buffer);
		char* content = buffer + sizeof(uint32_t);

		*len = value.length();
		snprintf(content, MAX_LEN, "%s", value.c_str());
	}

	void MqString::deserialize(char* buffer) {
		value = (buffer + sizeof(uint32_t));
	}
}
