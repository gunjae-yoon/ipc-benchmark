#include <ipc-benchmark/boost/trunk/publisher.h>
#include <ipc-benchmark/base/performance.h>
#include <guutil/log/logger.h>

namespace ipc_benchmark::trunk {
	extern guutil::log::Logger logger; // global logger

	Publisher::Publisher(std::string shmname, std::string topicname, uint64_t subscribers) {
		name.shm = shmname;
		name.topic = topicname;
		count = subscribers;
		targets.resize(count, {nullptr, nullptr});
	}

	Publisher::~Publisher() {
	}

	bool Publisher::ready() {
		segment = boost::interprocess::managed_shared_memory(boost::interprocess::open_only, name.shm.c_str());
		
		// TODO: need to make flexibly
		mutex = segment.find<boost::interprocess::interprocess_mutex>("TrunkMutex").first;
		if (mutex == nullptr) {
			return false;
		}

		SharedMap* shmmap = segment.find<SharedMap>(name.topic.c_str()).first;
		if (shmmap == nullptr) {
			return false;;
		}

		for (uint64_t idx = 0; idx < count; idx++) {
			const std::string shmcond = "TrunkCondition" + std::to_string(idx);
			targets[idx].cond = segment.find<boost::interprocess::interprocess_condition>(shmcond.c_str()).first;
			if (shmmap->find(idx) == shmmap->end()) {
				return false;
			}
			targets[idx].list = &shmmap->find(idx)->second;
			if ((targets[idx].cond == nullptr) || (targets[idx].list == nullptr)) {
				return false;
			}
		}
		return true;
	}

	void Publisher::run() {
		const ShmAllocator alloc(segment.get_segment_manager());
		uint64_t published = 0;
		while (published < Performance::DATA_AMOUNT) {
			boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(*mutex);
			for (Proxy& target : targets) {
				target.list->push_back(ShmString("value" + std::to_string(published), alloc));
				target.cond->notify_all();
			}
			published++;
		}
	}
}
