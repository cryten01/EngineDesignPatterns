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

		assert(m_SystemsMap.find(type) == m_SystemsMap.end() && "Registering system more than once.");

		// Create a pointer to the system and add it to the systems map
		std::shared_ptr<System> entry = std::make_shared<T>();

		m_SystemsMap.emplace(type, entry);
	}

	template<typename T>
	std::shared_ptr<T> GetSystem()
	{
		size_t type = typeid(T).hash_code();

		auto entry = m_SystemsMap.find(type)->second;

		return std::static_pointer_cast<T>(entry);
	}

	template<typename T>
	void RemoveSystem()
	{
		size_t type = typeid(T).hash_code();
		m_SystemsMap.erase(type);
	}

	template<typename T>
	void SetSignature(Signature signature)
	{
		size_t type = typeid(T).hash_code();

		assert(m_SystemsMap.find(type) != m_SystemsMap.end() && "System used before registered.");

		// Set the signature for this system
		m_Signatures.insert({ type, signature });
	}

	void OnEntityDestroyed(EntityID entity) 
	{
		// Erase a destroyed entity from all system lists
		// mEntities is a set so no check needed
		for (auto const& entry : m_SystemsMap)
		{
			auto const& system = entry.second;

			system->m_Entities.erase(entity);
		}
	}

	void OnEntitySignatureChanged(EntityID entity, Signature entitySignature)
	{
		// Notify each system that an entity's signature changed (occurs when a component is added, removed or an entity is destroyed)
		for (auto const& entry : m_SystemsMap)
		{
			auto const& type = entry.first;
			auto const& system = entry.second;
			auto const& systemSignature = m_Signatures[type];

			// Entity signature matches system signature - insert into set
			if ((entitySignature & systemSignature) == systemSignature)
			{
				system->m_Entities.insert(entity);
			}
			// Entity signature does not match system signature - erase from set
			else
			{
				system->m_Entities.erase(entity);
			}
		}
	}

private:
	// Map from type hash to a system pointer
	std::map<size_t, std::shared_ptr<System>> m_SystemsMap;

	// Map from type hash to a signature
	std::map<size_t, Signature> m_Signatures{};
};


