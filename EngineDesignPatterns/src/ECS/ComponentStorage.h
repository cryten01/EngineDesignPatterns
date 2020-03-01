#pragma once
#include <map>
#include <iostream>

#include "ECS.h"
#include "Event/Station.h"
#include "Event/EventTypes.h"


class IComponentStorageSystem
{};


template <typename T>
class ComponentStorageSystem : public IComponentStorageSystem
{
public:
	ComponentStorageSystem() 
	{
		// Lambdas enable direct contact to each storage without relying on virtual inherited methods.
		auto onEntityDestroyedFunction = [this](EntityDestroyedEvent e) -> bool
		{
			this->ClearEntry(e.id);
			return true;
		};

		m_OnEntityDestroyedID = StationSystem::Subscribe<EntityDestroyedEvent>(onEntityDestroyedFunction);
	}

	~ComponentStorageSystem() 
	{
		StationSystem::Unsubscribe<EntityDestroyedEvent>(m_OnEntityDestroyedID);
	}

	void MakeEntry(EntityID& entity, T value)
	{
		m_StorageArray[entity] = value;

		// TODO: Replacing a value is only possible by erasing the entity first
		//mStorageMap.erase(entity); 
		//mStorageMap.emplace(entity, value);
	}

	T& GetEntry(EntityID& entity)
	{
		return m_StorageArray[entity];

		//return mStorageMap.find(entity)->second;
	}

	void ClearEntry(EntityID& entity)
	{
		m_StorageMap.erase(entity);
		std::cout << "Clear entry from Storage" << std::endl;

		// TODO: Support entry deletion for array
	}

private:
	std::array<T, MAX_ENTITIES> m_StorageArray;	// O(1) access times
	size_t m_ArraySize = 0;

	std::map<EntityID, T> m_StorageMap;			// N-log(n) access times
	CallbackID m_OnEntityDestroyedID;
};