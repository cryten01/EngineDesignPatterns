#pragma once
#include <map>
#include <iostream>

#include "ECS.h"
#include "../Event/Station.h"
#include "../Testing/EventTypes.h"


class IComponentStorageSystem
{};


template <typename T>
class ComponentStorageSystem : public IComponentStorageSystem
{
public:
	ComponentStorageSystem() 
	{
		// Lambdas enable direct contact to each storage without relying on virtual inherited methods.
		auto OnEntityDestroyed = [this](EntityDestroyedEvent e) -> bool
		{
			this->ClearEntry(e.id);
			return true;
		};

		StationSystem::Subscribe<EntityDestroyedEvent>(OnEntityDestroyed);
	}

	void MakeEntry(EntityID& entity, T value)
	{
		// TODO: Replacing a value is only possible by erasing the entity first
		storageMap.erase(entity); 
		storageMap.emplace(entity, value);
	}

	T& GetEntry(EntityID& entity)
	{
		return storageMap.find(entity)->second;
	}

	void ClearEntry(EntityID& entity)
	{
		storageMap.erase(entity);
		std::cout << "Clear entry from Storage" << std::endl;
	}

private:
	// N-log(n) access times
	std::map<EntityID, T> storageMap;
};