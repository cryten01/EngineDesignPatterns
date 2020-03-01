#pragma once
#include <queue>
#include <vector>
#include <array>
#include <bitset>
#include <assert.h>

#include "ECS.h"
#include "ECS/System.h"
#include "Event/Station.h"
#include "Event/EventTypes.h"


struct EntityManagerData
{
	// Total living entities - used to keep limits on how many exist
	size_t livingEntities{};

	// Queue of unused entity IDs
	std::queue<EntityID> availableEntities{};

	// Array of signatures where the index corresponds to the entity ID
	std::array<Signature, MAX_ENTITIES> signatures{};
};


class EntityManager : public System
{
public:
	EntityManager() 
	{
		// Initialize the queue with all possible entity IDs
		for (EntityID entity = 0; entity < MAX_ENTITIES; ++entity)
		{
			m_Factory.availableEntities.push(entity);
		}
	}

	EntityID CreateEntity()
	{
		assert(m_Factory.livingEntities < MAX_ENTITIES && "Too many entities in existence.");

		// Take an ID from the front of the queue
		EntityID id = m_Factory.availableEntities.front();
		m_Factory.availableEntities.pop();
		++m_Factory.livingEntities;

		return id;
	}

	void DestroyEntity(EntityID entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Invalidate the returned entity's signature
		m_Factory.signatures[entity].reset();

		// Put the returned ID at the back of the queue
		m_Factory.availableEntities.push(entity);
		--m_Factory.livingEntities;

		// Notify storages over station that entity has been returned
		EntityDestroyedEvent event;
		event.id = entity;
		StationSystem::Publish(event);
	}

	void SetSignature(EntityID entity, Signature signature)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Put this entity's signature into the array
		m_Factory.signatures[entity] = signature;
	}

	Signature GetSignature(EntityID entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Get this entity's signature from the array
		return m_Factory.signatures[entity];
	}

private:
	EntityManagerData m_Factory;
};
