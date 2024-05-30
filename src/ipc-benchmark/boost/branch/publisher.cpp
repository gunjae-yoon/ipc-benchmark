#include <ipc-benchmark/boost/branch/publisher.h>
#include <ipc-benchmark/base/performance.h>
#include <guutil/log/logger.h>

#define __CLASS__ "[branch::Publisher]"

namespace ipc_benchmark {
	extern guutil::log::Logger logger; // global logger
}

namespace ipc_benchmark::branch {

	Publisher::Publisher(std::list<Proxy>& targets) {
		for (Proxy& target : targets) {
			proxies.push_back({target.name, nullptr});
		}
	}

	Publisher::~Publisher() {
	}

	bool Publisher::ready() {
		for (Proxy& proxy : proxies) {
			proxy.obj = new Object();
			if (proxy.obj == nullptr) {
				return false;
			}

			proxy.obj->segment = boost::interprocess::managed_shared_memory(boost::interprocess::open_only, proxy.name.shm.c_str());
			proxy.obj->mutex = proxy.obj->segment.find<boost::interprocess::interprocess_mutex>(proxy.name.mutex.c_str()).first;
			proxy.obj->cond = proxy.obj->segment.find<boost::interprocess::interprocess_condition>(proxy.name.cond.c_str()).first;
			proxy.obj->map = proxy.obj->segment.find<SharedMap>(proxy.name.topic.c_str()).first;
			proxy.obj->list = &(proxy.obj->map->find(proxy.name.id)->second);
		}

		return true;
	}

	void Publisher::run() {
		uint64_t published = 0;
		while (published < Performance::DATA_AMOUNT) {
			for (Proxy& proxy: proxies) {
				boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(*(proxy.obj->mutex));
				proxy.obj->list->push_back(ShmString("value", proxy.obj->segment.get_segment_manager()));
				proxy.obj->cond->notify_all();
			}
			published++;
		}
	}
}
