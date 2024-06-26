#ifndef __ipc_benchmark_boost_types_h__
#define __ipc_benchmark_boost_types_h__

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/list.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include <cstdint>

namespace ipc_benchmark {
	// Typedefs for convenience
	typedef boost::interprocess::allocator<char, boost::interprocess::managed_shared_memory::segment_manager> CharAllocator;
	typedef boost::interprocess::basic_string<char, std::char_traits<char>, CharAllocator> ShmString;
	typedef boost::interprocess::allocator<ShmString, boost::interprocess::managed_shared_memory::segment_manager> StringAllocator;
	typedef boost::interprocess::list<ShmString, StringAllocator> ShmStringList;

	typedef uint64_t KeyType;
	typedef std::pair<const KeyType, ShmStringList> ValueType;

	// Custom comparator
	struct KeyCompare : public std::binary_function<KeyType, KeyType, bool> {
   		bool operator() (const KeyType &a, const KeyType &b) const {
			return a < b;
		}
	};

	// Allocator and map typedefs
	typedef boost::interprocess::allocator<ValueType, boost::interprocess::managed_shared_memory::segment_manager> ShmAllocator;
	typedef boost::interprocess::map<KeyType, ShmStringList, KeyCompare, ShmAllocator> SharedMap;

}

#endif
