#pragma once

#include <assert.h>

#include "ECS/System.h"
#include "ECS/ComponentStorage.h"
#include "Event/Station.h"


class ComponentManager : public System
{
public:
	template<typename T>
	void AddStorage()
	{
		size_t type = typeid(T).hash_code();

		assert(m_ComponentTypes.find(type) == m_ComponentTypes.end() && "Adding storage for component type more than once.");

		// Add this component type to the component type map
		m_ComponentTypes.insert({ type, m_NextComponentType });

		// Create a component storage pointer and add it to the storage map
		auto entry = std::make_shared<ComponentStorageSystem<T>>();
		m_StorageMap.emplace(type, entry);

		// Increment the value so that the next component registered will be different
		++m_NextComponentType;
	}

	template<typename T>
	std::shared_ptr<ComponentStorageSystem<T>> GetStorage()
	{
		size_t type = typeid(T).hash_code();

		assert(m_ComponentTypes.find(type) != m_ComponentTypes.end() && "Component not registered before use.");

		auto entry = m_StorageMap.find(type)->second;

		return std::static_pointer_cast<ComponentStorageSystem<T>>(entry);
	}

	template<typename T>
	void RemoveStorage()
	{
		size_t type = typeid(T).hash_code();
		m_StorageMap.erase(type);
	}

public:
	template<typename T>
	void AddComponent(EntityID& entity, T value)
	{
		// Add a component to the storage for an entity
		std::shared_ptr<ComponentStorageSystem<T>> system = GetStorage<T>();

		system->MakeEntry(entity, value);
	}

	template<typename T>
	ComponentID GetComponentType()
	{
		size_t type = typeid(T).hash_code();

		assert(m_ComponentTypes.find(type) != m_ComponentTypes.end() && "Component not registered before use.");

		// Return this component's type - used for creating signatures
		return m_ComponentTypes[type];
	}

	template<typename T>
	T& GetComponent(EntityID& entity)
	{
		// Get a reference to a component from the storage for an entity
		std::shared_ptr<ComponentStorageSystem<T>> system = GetStorage<T>();

		return system->GetEntry(entity);
	}

	template<typename T>
	void RemoveComponent(EntityID& entity)
	{
		// Remove a component from the storage for an entity
		std::shared_ptr<ComponentStorageSystem<T>> system = GetStorage<T>();

		system->ClearEntry(entity);
	}

private:
	// The component type to be assigned to the next registered component - starting at 0
	ComponentID m_NextComponentType{};

	// Map from type hash code to a component id
	std::map<size_t, ComponentID> m_ComponentTypes{};

	// Map from type hash code to a storage
	std::map<size_t, std::shared_ptr<IComponentStorageSystem>> m_StorageMap{};
};


