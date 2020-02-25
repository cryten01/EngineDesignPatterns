#pragma once

#include <map>
#include <iostream>

#include "ECS/ECS.h"
#include "ECS/System.h"


class SystemManager
{
public:
	template<typename T>
	void AddSystem()
	{
		size_t type = typeid(T).hash_code();

		assert(systemsMap.find(type) == systemsMap.end() && "Registering system more than once.");

		// Create a pointer to the system and add it to the systems map
		std::shared_ptr<System> entry = std::make_shared<T>();

		systemsMap.emplace(type, entry);
	}

	template<typename T>
	std::shared_ptr<T> GetSystem()
	{
		size_t type = typeid(T).hash_code();

		auto entry = systemsMap.find(type)->second;

		return std::static_pointer_cast<T>(entry);
	}

	template<typename T>
	void RemoveSystem()
	{
		size_t type = typeid(T).hash_code();
		systemsMap.erase(type);
	}

	template<typename T>
	void SetSignature(Signature signature)
	{
		size_t type = typeid(T).hash_code();

		assert(systemsMap.find(type) != systemsMap.end() && "System used before registered.");

		// Set the signature for this system
		mSignatures.insert({ type, signature });
	}

	void OnEntityDestroyed(EntityID entity) 
	{
		// Erase a destroyed entity from all system lists
		// mEntities is a set so no check needed
		for (auto const& entry : systemsMap)
		{
			auto const& system = entry.second;

			system->mEntities.erase(entity);
		}
	}

	void OnEntitySignatureChanged(EntityID entity, Signature entitySignature)
	{
		// Notify each system that an entity's signature changed (occurs when a component is added, removed or an entity is destroyed)
		for (auto const& entry : systemsMap)
		{
			auto const& type = entry.first;
			auto const& system = entry.second;
			auto const& systemSignature = mSignatures[type];

			// Entity signature matches system signature - insert into set
			if ((entitySignature & systemSignature) == systemSignature)
			{
				system->mEntities.insert(entity);
			}
			// Entity signature does not match system signature - erase from set
			else
			{
				system->mEntities.erase(entity);
			}
		}
	}

private:
	// Map from type hash to a system pointer
	std::map<size_t, std::shared_ptr<System>> systemsMap;

	// Map from type hash to a signature
	std::map<size_t, Signature> mSignatures{};
};


