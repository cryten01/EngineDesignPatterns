#pragma once

#include <memory>

#include "ECS/ComponentManager.h"
#include "ECS/EntityManager.h"
#include "ECS/SystemManager.h"
#include "ECS/ECS.h"


class Coordinator
{
public:
	void Init()
	{
		// Create pointers to each manager
		mComponentManager = std::make_unique<ComponentManager>();
		mEntityManager = std::make_unique<EntityManager>();
		mSystemManager = std::make_unique<SystemManager>();
	}


	// Entity methods
	EntityID CreateEntity()
	{
		return mEntityManager->CreateEntity();
	}

	void DestroyEntity(EntityID entity)
	{
		mEntityManager->DestroyEntity(entity);

		mSystemManager->OnEntityDestroyed(entity);
	}


	// Component methods
	template<typename T>
	void RegisterComponent()
	{
		mComponentManager->AddStorage<T>();
	}

	template<typename T>
	void DeregisterComponent()
	{
		mComponentManager->RemoveStorage<T>();
	}

	template<typename T>
	void AddComponent(EntityID entity, T component)
	{
		mComponentManager->AddComponent<T>(entity, component);

		auto signature = mEntityManager->GetSignature(entity);
		signature.set(mComponentManager->GetComponentType<T>(), true);
		mEntityManager->SetSignature(entity, signature);

		mSystemManager->OnEntitySignatureChanged(entity, signature);
	}

	template<typename T>
	void RemoveComponent(EntityID entity)
	{
		mComponentManager->RemoveComponent<T>(entity);

		auto signature = mEntityManager->GetSignature(entity);
		signature.set(mComponentManager->GetComponentType<T>(), false);
		mEntityManager->SetSignature(entity, signature);

		mSystemManager->OnEntitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& GetComponent(EntityID entity)
	{
		return mComponentManager->GetComponent<T>(entity);
	}

	template<typename T>
	ComponentID GetComponentType()
	{
		return mComponentManager->GetComponentType<T>();
	}

	template<typename T>
	std::shared_ptr<ComponentStorageSystem<T>> GetComponentStorage()
	{
		return mComponentManager->GetStorage<T>();
	}


	// System methods
	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		mSystemManager->AddSystem<T>();
		return GetSystem<T>();
	}

	template<typename T>
	std::shared_ptr<T> GetSystem()
	{
		return mSystemManager->GetSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(Signature signature)
	{
		mSystemManager->SetSignature<T>(signature);
	}

private:
	std::unique_ptr<ComponentManager> mComponentManager;
	std::unique_ptr<EntityManager> mEntityManager;
	std::unique_ptr<SystemManager> mSystemManager;
};
