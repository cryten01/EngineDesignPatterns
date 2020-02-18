#pragma once
#include "DataStorage.h"
#include "System.h"

// aka Component Manager

struct DataRegistryData
{
	std::map<size_t, std::shared_ptr<DataStorageSystem>> registerMap;
};


class DataRegistrySystem : public System
{
public:
	template<typename T>
	void RegisterStorageSystem(DataRegistryData& r)
	{
		size_t type = typeid(T).hash_code();
		auto entry = std::make_shared<TDataStorageSystem<T>>();
		r.registerMap.emplace(type, entry);
	}

	template<typename T>
	void DeregisterStorageSystem(DataRegistryData& r)
	{
		size_t type = typeid(T).hash_code();
		r.registerMap.erase(type);
	}

	template<typename T>
	void MakeEntry(DataRegistryData& r, Key& key, T value)
	{
		std::shared_ptr<TDataStorageSystem<T>> system = GetStorageSystem<T>(r);
		
		system->MakeEntry(key, value);
	}

	template<typename T>
	T& GetEntry(DataRegistryData& r, Key& key)
	{
		std::shared_ptr<TDataStorageSystem<T>> system = GetStorageSystem<T>(r);

		return system->GetEntry(key);
	}

	template<typename T>
	void ClearEntry(DataRegistryData& r, Key& key)
	{
		std::shared_ptr<TDataStorageSystem<T>> system = GetStorageSystem<T>(r);

		system->ClearEntry(key);
	}

	void ClearAllEntries(DataRegistryData& r, Key& key)
	{
		for (auto entry : r.registerMap) 
		{
			entry.second->ClearEntry(key);
		}
	}

private:
	template<typename T>
	std::shared_ptr<TDataStorageSystem<T>> GetStorageSystem(DataRegistryData& r)
	{
		size_t type = typeid(T).hash_code();
		auto entry = r.registerMap.find(type)->second;
		return std::static_pointer_cast<TDataStorageSystem<T>>(entry);
	}
};


