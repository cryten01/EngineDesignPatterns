#pragma once
#include <map>

#include "../FDC/DataSet.h"
#include "EntityFactory.h"
#include "Data.h"


class StorageSystem
{
public:
	virtual ~StorageSystem() = default;
	virtual void ClearEntry(Entity& entity) = 0;
};


template <typename T>
class TStorageSystem : public StorageSystem
{
public:
	void MakeEntry(Entity& entity, T value)
	{
		storageMap.erase(entity); // TODO: Replacing a value is only possible by erasing the entity first
		storageMap.emplace(entity, value);
	}

	T& GetEntry(Entity& entity)
	{
		return storageMap.find(entity)->second;
	}

	virtual void ClearEntry(Entity& entity) override
	{
		storageMap.erase(entity);
		std::cout << "Clear entry from Storage" << std::endl;
	}

private:
	std::map<Entity, T> storageMap; // n-log(n) access times
};