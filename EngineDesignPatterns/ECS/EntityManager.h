#pragma once
#include <queue>
#include <vector>
#include <array>
#include <bitset>

#include "ECS.h"
#include "System.h"
#include "Event/Station.h"


struct EntityManagerData
{
	// Total living entities - used to keep limits on how many exist
	size_t livingEntities{};

	// Queue of unused entity IDs
	std::queue<EntityID> availableEntities{};

	// Array of signatures where the index corresponds to the entity ID
	std::array<Signature, MAX_ENTITIES> signatures{};
};

class EntityManagerSystem : public System
{
public:
	EntityManagerSystem() 
	{
		// Initialize the queue with all possible entity IDs
		for (EntityID entity = 0; entity < MAX_ENTITIES; ++entity)
		{
			factory.availableEntities.push(entity);
		}
	}

	EntityID IssueEntity()
	{
		assert(factory.livingEntities < MAX_ENTITIES && "Too many entities in existence.");

		// Take an ID from the front of the queue
		EntityID id = factory.availableEntities.front();
		factory.availableEntities.pop();
		++factory.livingEntities;

		return id;
	}

	void ReturnEntity(EntityID entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Invalidate the returned entity's signature
		factory.signatures[entity].reset();

		// Put the returned ID at the back of the queue
		factory.availableEntities.push(entity);
		--factory.livingEntities;

		// Notify storages over station that entity has been returned
		StationSystem::Publish<EntityID>(entity);
	}

	void SetSignature(EntityID entity, Signature signature)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Put this entity's signature into the array
		factory.signatures[entity] = signature;
	}

	Signature GetSignature(EntityID entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Get this entity's signature from the array
		return factory.signatures[entity];
	}

private:
	EntityManagerData factory;
};
