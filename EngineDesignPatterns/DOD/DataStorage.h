#pragma once
#include <map>

#include "../FDC/DataSet.h"
#include "Key.h"

/**
 * Pros:
 *	Variable map size
 *	No empty spots
 *	No size per runtime necessary
 * Cons:
 *	N log n access times
 */
 // aka Component Array



struct DataStorage
{};

template <typename T>
struct TStorage : DataStorage
{
	std::map<Key, T> storageMap;
};

template<typename T>
void MakeEntry(std::shared_ptr<TStorage<T>> storage, Key& key, T value)
{
	storage->storageMap.emplace(key, value);
}

template<typename T>
T& GetEntry(std::shared_ptr<TStorage<T>> storage, Key& key)
{
	return storage->storageMap.find(key)->second;
}

template<typename T>
void ClearEntry(std::shared_ptr<TStorage<T>> storage, Key& key)
{
	storage->storageMap.erase(key);
}