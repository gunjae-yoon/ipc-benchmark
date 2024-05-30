#include <ipc-benchmark/posix/base/mqstring.h>
#include <cstdlib>

namespace ipc_benchmark {
	const uint64_t MqString::MAX_LEN = 256;
	const uint64_t MqString::BUF_LEN = (256 + sizeof(uint32_t));

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
