#pragma once
#include <map>

#include "../FDC/DataSet.h"
#include "Key.h"
#include "Data.h"


class StorageSystem
{
public:
	virtual ~StorageSystem() = default;
	virtual void ClearEntry(Key& key) = 0;
};


template <typename T>
class TStorageSystem : public StorageSystem
{
public:
	void MakeEntry(Key& key, T value)
	{
		storageMap.erase(key); // TODO: Replacing a value is only possible by erasing the key first
		storageMap.emplace(key, value);
	}

	T& GetEntry(Key& key)
	{
		return storageMap.find(key)->second;
	}

	virtual void ClearEntry(Key& key) override
	{
		storageMap.erase(key);
	}

private:
	std::map<Key, T> storageMap; // N log(n) access times
};