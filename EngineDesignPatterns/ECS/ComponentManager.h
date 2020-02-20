#pragma once
#include "ComponentStorage.h"
#include "System.h"
#include "Event/Station.h"

// Aka Component Manager
class ComponentManagerSystem : public System
{
public:
	ComponentManagerSystem() 
	{
		auto onEntityReturned = [this](EntityID e) -> bool
		{
			this->RemoveAllComponents(e);

			return true;
		};

		StationSystem::Subscribe<EntityID>(onEntityReturned);
	}

	template<typename T>
	void AddStorage()
	{
		size_t type = typeid(T).hash_code();

		auto entry = std::make_shared<ComponentStorageSystem<T>>();

		storageSystemMap.emplace(type, entry);
	}

	template<typename T>
	std::shared_ptr<ComponentStorageSystem<T>> GetStorage()
	{
		size_t type = typeid(T).hash_code();

		auto entry = storageSystemMap.find(type)->second;

		return std::static_pointer_cast<ComponentStorageSystem<T>>(entry);
	}

	template<typename T>
	void RemoveStorage()
	{
		size_t type = typeid(T).hash_code();
		storageSystemMap.erase(type);
	}

public:
	template<typename T>
	void AddComponent(EntityID& entity, T value)
	{
		std::shared_ptr<ComponentStorageSystem<T>> system = GetStorage<T>();

		system->MakeEntry(entity, value);
	}

	template<typename T>
	T& GetComponent(EntityID& entity)
	{
		std::shared_ptr<ComponentStorageSystem<T>> system = GetStorage<T>();

		return system->GetEntry(entity);
	}

	template<typename T>
	void RemoveComponent(EntityID& entity)
	{
		std::shared_ptr<ComponentStorageSystem<T>> system = GetStorage<T>();

		system->ClearEntry(entity);
	}

	void RemoveAllComponents(EntityID& entity)
	{
		for (auto entry : storageSystemMap)
		{
			entry.second->ClearEntry(entity);
		}
	}

private:
	std::map<size_t, std::shared_ptr<IComponentStorageSystem>> storageSystemMap; // links to storages for each data type
};


