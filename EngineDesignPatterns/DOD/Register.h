#pragma once
#include "Storage.h"

// aka Component Manager

struct Register
{
	std::map<size_t, std::shared_ptr<StorageSystem>> registerMap;
};


class RegisterSystem
{
public:
	template<typename T>
	void RegisterStorageSystem(Register& r)
	{
		size_t type = typeid(T).hash_code();
		auto entry = std::make_shared<TStorageSystem<T>>();
		r.registerMap.emplace(type, entry);
	}

	template<typename T>
	void DeregisterStorageSystem(Register& r)
	{
		size_t type = typeid(T).hash_code();
		r.registerMap.erase(type);
	}

	template<typename T>
	void MakeEntry(Register& r, Key& key, T value)
	{
		std::shared_ptr<TStorageSystem<T>> system = GetStorageSystem<T>(r);
		
		system->MakeEntry(key, value);
	}

	template<typename T>
	T& GetEntry(Register& r, Key& key)
	{
		std::shared_ptr<TStorageSystem<T>> system = GetStorageSystem<T>(r);

		return system->GetEntry(key);
	}

	template<typename T>
	void ClearEntry(Register& r, Key& key)
	{
		std::shared_ptr<TStorageSystem<T>> system = GetStorageSystem<T>(r);

		system->ClearEntry(key);
	}

	void ClearAllEntries(Register& r, Key& key)
	{
		// Clear key entries in relevant storages
		for (auto entry : r.registerMap) 
		{
			entry.second->ClearEntry(key);
		}
	}

private:
	template<typename T>
	std::shared_ptr<TStorageSystem<T>> GetStorageSystem(Register& r)
	{
		size_t type = typeid(T).hash_code();
		auto entry = r.registerMap.find(type)->second;
		return std::static_pointer_cast<TStorageSystem<T>>(entry);
	}
};


