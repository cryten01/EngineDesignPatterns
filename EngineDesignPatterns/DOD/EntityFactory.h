#pragma once
#include <queue>
#include <vector>
#include <cstdint>

#include "System.h"
#include "Station.h"

// A simple type alias (helps in changing data type if necessary)
using Entity = std::uint32_t;


struct EntityFactoryData
{
	Entity entityCreator;
	std::queue<Entity> freeEntities;
};


class EntityFactorySystem : public System
{
public:
	void ReturnEntity(EntityFactoryData& factory, Entity entity)
	{
		// Recycle entity
		factory.freeEntities.push(entity);

		// Notify storages over station that entity has been returned
		StationSystem::Publish<Entity>(entity);
	}

	Entity IssueEntity(EntityFactoryData& factory)
	{
		if (!factory.freeEntities.empty())
		{
			Entity entity = factory.freeEntities.front();
			factory.freeEntities.pop();
			return entity;
		}
		else
		{
			factory.entityCreator++;
			return factory.entityCreator;
		}
	}
};
