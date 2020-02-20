#pragma once
#include <queue>
#include <vector>
#include <array>
#include <bitset>

#include "Entity.h"
#include "System.h"
#include "Station.h"


struct EntityManagerData
{
	EntityID livingEntities = 0; // shows how many entities are currently in use

	std::queue<EntityID> availableEntities{};

	std::bitset<MAX_ENTITIES> usedEntities{}; // 0 = unused / 1 = used / index = id

	std::array<Signature, MAX_ENTITIES> signatures{};
};

class EntityManagerSystem : public System
{
public:
	EntityID IssueEntity(EntityManagerData& factory)
	{
		if (factory.availableEntities.size() > 0)
		{
			EntityID entity = factory.availableEntities.front();
			factory.availableEntities.pop();
			return entity;
		}
		else
		{
			factory.livingEntities++;
			return factory.livingEntities;
		}
	}

	void ReturnEntity(EntityManagerData& factory, EntityID entity)
	{
		// Reset components signature to 0
		factory.signatures[entity].reset();

		// Recycle entity
		factory.availableEntities.push(entity);

		// Notify storages over station that entity has been returned
		StationSystem::Publish<EntityID>(entity);
	}

	void SetSignature(EntityManagerData& factory, EntityID entity, Signature signature)
	{
		factory.signatures[entity] = signature;
	}

	Signature GetSignature(EntityManagerData& factory, EntityID entity)
	{
		return factory.signatures[entity];
	}
};
