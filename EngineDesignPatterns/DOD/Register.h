#pragma once
#include "Storage.h"

// aka Component Manager

struct RegisterData
{
	std::map<size_t, std::shared_ptr<Storage>> registerMap;
};

template<typename T>
void AddStorage(RegisterData& r)
{
	size_t type = typeid(T).hash_code();

	std::shared_ptr<Storage> entry = std::make_shared<TStorage<T>>();

	r.registerMap.emplace(type, entry);
}

template<typename T>
std::shared_ptr<TStorage<T>> GetStorage(RegisterData& r)
{
	size_t type = typeid(T).hash_code();

	std::shared_ptr<Storage> entry = r.registerMap.find(type)->second;

	return std::static_pointer_cast<TStorage<T>>(entry);
}

template<typename T>
void RemoveStorage(RegisterData& r)
{
	size_t type = typeid(T).hash_code();
	r.registerMap.erase(type);
}




template<typename T>
void MakeEntry(RegisterData& r, Key& key, T value)
{
	MakeEntry(GetStorage<T>(r), key, value);
}

template<typename T>
T& GetEntry(RegisterData& r, Key& key)
{
	return GetEntry(GetStorage<T>(r), key);
}

template<typename T>
void ClearEntry(RegisterData& r, Key& key)
{
	ClearEntry(GetStorage<T>(r), key);
}


