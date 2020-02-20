#pragma once
#include <map>

#include "../FDC/DataSet.h"
#include "Entity.h"
#include "Component.h"


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
		storageMap.erase(entity); // TODO: Replacing a value is only possible by erasing the entity first
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
	std::map<EntityID, T> storageMap; // n-log(n) access times
};