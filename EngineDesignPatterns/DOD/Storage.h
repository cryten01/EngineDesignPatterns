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

template <typename T>
struct Storage
{
	std::map<Key, T> map;
};


template<typename T>
void MakeEntry(Storage<T>& storage, Key& key, T value)
{
	storage.map.emplace(key, value);
}

template<typename T>
T& GetEntry(Storage<T>& storage, Key& key)
{
	return storage.map.find(key)->second;
}

template<typename T>
void ClearEntry(Storage<T>& storage, Key& key)
{
	storage.map.erase(key);
}