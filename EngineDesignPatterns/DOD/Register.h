#pragma once
#include "Storage.h"

// aka Component Manager

struct Register
{
	std::map<size_t, std::shared_ptr<Storage>> registerMap;
};

template<typename T>
void AddStorage(Register& r)
{
	size_t type = typeid(T).hash_code();
	auto entry = std::make_shared<TStorage<T>>();
	r.registerMap.emplace(type, entry);
}

template<typename T>
std::shared_ptr<TStorage<T>> GetStorage(Register& r)
{
	size_t type = typeid(T).hash_code();
	auto entry = r.registerMap.find(type)->second;
	return std::static_pointer_cast<TStorage<T>>(entry);
}

template<typename T>
void RemoveStorage(Register& r)
{
	size_t type = typeid(T).hash_code();
	r.registerMap.erase(type);
}


void OnKeyReturn(Register& r, Key& key)
{
	// Clear key entries in relevant storages
	//for (auto entries : r.registerMap) 
	//{
	//	ClearEntry(entries.second, key);
	//}
}

template<typename T>
void MakeEntry(Register& r, Key& key, T value)
{
	auto storage = GetStorage<T>(r);
	MakeEntry<T>(storage, key, value);
}

template<typename T>
T& GetEntry(Register& r, Key& key)
{
	auto storage = GetStorage<T>(r);
	auto entry = GetEntry<T>(storage, key);
	return entry;
}

template<typename T>
void ClearEntry(Register& r, Key& key)
{
	auto storage = GetStorage<T>(r);
	ClearEntry(storage, key);
}


