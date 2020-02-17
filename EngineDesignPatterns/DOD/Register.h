#pragma once
#include "DataStorage.h"

// aka Component Manager

struct StorageRegister
{
	std::map<size_t, std::shared_ptr<DataStorage>> registerMap;
};

template<typename T>
void AddStorage(StorageRegister& r)
{
	size_t type = typeid(T).hash_code();

	std::shared_ptr<DataStorage> entry = std::make_shared<TStorage<T>>();

	r.registerMap.emplace(type, entry);
}

template<typename T>
std::shared_ptr<TStorage<T>> GetStorage(StorageRegister& r)
{
	size_t type = typeid(T).hash_code();

	std::shared_ptr<DataStorage> entry = r.registerMap.find(type)->second;

	return std::static_pointer_cast<TStorage<T>>(entry);
}

template<typename T>
void RemoveStorage(StorageRegister& r)
{
	size_t type = typeid(T).hash_code();
	r.registerMap.erase(type);
}


bool OnKeyReturn(StorageRegister& r, Key key)
{
	// Clear key entries in relevant storages
	// Bit set defines which storages are needed
	return true;
}

template<typename T>
void MakeEntry(StorageRegister& r, Key& key, T value)
{
	MakeEntry(GetStorage<T>(r), key, value);
}

template<typename T>
T& GetEntry(StorageRegister& r, Key& key)
{
	return GetEntry(GetStorage<T>(r), key);
}

template<typename T>
void ClearEntry(StorageRegister& r, Key& key)
{
	ClearEntry(GetStorage<T>(r), key);
}


