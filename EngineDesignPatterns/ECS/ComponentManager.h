#pragma once

#include "System.h"
#include "Component.h"
#include "ComponentStorage.h"

#include "Event/Station.h"


class ComponentManager : public System
{
public:
	ComponentManager() 
	{
		auto onEntityReturned = [this](EntityID e) -> bool
		{
			this->OnEntityDestroyed(e);

			return true;
		};

		StationSystem::Subscribe<EntityID>(onEntityReturned);
	}

	template<typename T>
	void RegisterComponentStorage()
	{
		size_t type = typeid(T).hash_code();

		assert(componentTypes.find(type) == componentTypes.end() && "Adding storage for component type more than once.");

		// Add this component type to the component type map
		componentTypes.insert({ type, nextComponentType });

		// Create a component storage pointer and add it to the storage map
		auto entry = std::make_shared<ComponentStorageSystem<T>>();
		storageMap.emplace(type, entry);

		// Increment the value so that the next component registered will be different
		++nextComponentType;
	}

	template<typename T>
	std::shared_ptr<ComponentStorageSystem<T>> GetStorage()
	{
		size_t type = typeid(T).hash_code();

		assert(componentTypes.find(type) != componentTypes.end() && "Component not registered before use.");

		auto entry = storageMap.find(type)->second;

		return std::static_pointer_cast<ComponentStorageSystem<T>>(entry);
	}

	template<typename T>
	void RemoveStorage()
	{
		size_t type = typeid(T).hash_code();
		storageMap.erase(type);
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

		assert(componentTypes.find(type) != componentTypes.end() && "Component not registered before use.");

		// Return this component's type - used for creating signatures
		return componentTypes[type];
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

	void OnEntityDestroyed(EntityID& entity)
	{
		// Notify each component storage that an entity has been destroyed
		// If it has a component for that entity, it will remove it
		for (auto entry : storageMap)
		{
			entry.second->ClearEntry(entity);
		}
	}

private:
	// The component type to be assigned to the next registered component - starting at 0
	ComponentID nextComponentType{};

	// Map from type hash code to a component id
	std::map<size_t, ComponentID> componentTypes{};

	// Map from type hash code to a storage
	std::map<size_t, std::shared_ptr<IComponentStorageSystem>> storageMap{};
};


