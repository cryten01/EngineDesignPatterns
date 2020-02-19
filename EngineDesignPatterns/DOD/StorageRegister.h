#pragma once
#include "Storage.h"
#include "System.h"
#include "Station.h"

// Aka Component Manager
class StorageRegister : public System
{
public:
	StorageRegister() 
	{
		auto lambda = [this](Entity e) -> bool
		{
			this->ClearAllEntries(e);
			return true;
		};

		std::cout << "Created Storage Register lambda()" << std::endl;
		StationSystem::Subscribe<Entity>(lambda);
	}

	template<typename T>
	void AddStorage()
	{
		size_t type = typeid(T).hash_code();
		auto entry = std::make_shared<TStorageSystem<T>>();
		registerMap.emplace(type, entry);
	}

	template<typename T>
	std::shared_ptr<TStorageSystem<T>> GetStorage()
	{
		size_t type = typeid(T).hash_code();
		auto entry = registerMap.find(type)->second;
		return std::static_pointer_cast<TStorageSystem<T>>(entry);
	}

	template<typename T>
	void RemoveStorage()
	{
		size_t type = typeid(T).hash_code();
		registerMap.erase(type);
	}

public:
	template<typename T>
	void MakeEntry(Entity& entity, T value)
	{
		std::shared_ptr<TStorageSystem<T>> system = GetStorage<T>();

		system->MakeEntry(entity, value);
	}

	template<typename T>
	T& GetEntry(Entity& entity)
	{
		std::shared_ptr<TStorageSystem<T>> system = GetStorage<T>();

		return system->GetEntry(entity);
	}

	template<typename T>
	void ClearEntry(Entity& entity)
	{
		std::shared_ptr<TStorageSystem<T>> system = GetStorage<T>();

		system->ClearEntry(entity);
	}

	void ClearAllEntries(Entity& entity)
	{
		for (auto entry : registerMap)
		{
			entry.second->ClearEntry(entity);
		}
	}

private:
	std::map<size_t, std::shared_ptr<StorageSystem>> registerMap; // links to storages for each data type
};


