#pragma once
#include <map>

#include "ECS.h"

/**
 * This interface is needed so that the component manager 
 * can tell a generic Component Storage that an entity has been destroyed
 * and therefore need to update its entry.
 *
 * TODO: Use station and lambdas for directly contacting each storage.
 */
class IComponentStorageSystem
{
public:
	virtual ~IComponentStorageSystem() = default;
	virtual void ClearEntry(EntityID& entity) = 0;
};


template <typename T>
class ComponentStorageSystem : public IComponentStorageSystem
{
public:
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

	virtual void ClearEntry(EntityID& entity) override
	{
		storageMap.erase(entity);
		std::cout << "Clear entry from Storage" << std::endl;
	}

private:
	// N-log(n) access times
	std::map<EntityID, T> storageMap;
};