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
		auto onEntityDestroyedFunction = [this](EntityDestroyedEvent e) -> bool
		{
			this->ClearEntry(e.id);
			return true;
		};

		mOnEntityDestroyedID = StationSystem::Subscribe<EntityDestroyedEvent>(onEntityDestroyedFunction);
	}

	~ComponentStorageSystem() 
	{
		StationSystem::Unsubscribe<EntityDestroyedEvent>(mOnEntityDestroyedID);
	}

	void MakeEntry(EntityID& entity, T value)
	{
		// TODO: Replacing a value is only possible by erasing the entity first
		mStorageMap.erase(entity); 
		mStorageMap.emplace(entity, value);
	}

	T& GetEntry(EntityID& entity)
	{
		return mStorageMap.find(entity)->second;
	}

	void ClearEntry(EntityID& entity)
	{
		mStorageMap.erase(entity);
		std::cout << "Clear entry from Storage" << std::endl;
	}

private:
	std::map<EntityID, T> mStorageMap; // N-log(n) access times
	CallbackID mOnEntityDestroyedID;
};