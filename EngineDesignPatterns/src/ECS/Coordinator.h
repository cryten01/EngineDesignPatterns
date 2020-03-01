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
		m_ComponentManager = std::make_unique<ComponentManager>();
		m_EntityManager = std::make_unique<EntityManager>();
		m_SystemManager = std::make_unique<SystemManager>();
	}


	// Entity methods
	EntityID CreateEntity()
	{
		return m_EntityManager->CreateEntity();
	}

	void DestroyEntity(EntityID entity)
	{
		m_EntityManager->DestroyEntity(entity);

		m_SystemManager->OnEntityDestroyed(entity);
	}


	// Component methods
	template<typename T>
	void RegisterComponent()
	{
		m_ComponentManager->AddStorage<T>();
	}

	template<typename T>
	void DeregisterComponent()
	{
		m_ComponentManager->RemoveStorage<T>();
	}

	template<typename T>
	void AddComponent(EntityID entity, T component)
	{
		m_ComponentManager->AddComponent<T>(entity, component);

		auto signature = m_EntityManager->GetSignature(entity);
		signature.set(m_ComponentManager->GetComponentType<T>(), true);
		m_EntityManager->SetSignature(entity, signature);

		m_SystemManager->OnEntitySignatureChanged(entity, signature);
	}

	template<typename T>
	void RemoveComponent(EntityID entity)
	{
		m_ComponentManager->RemoveComponent<T>(entity);

		auto signature = m_EntityManager->GetSignature(entity);
		signature.set(m_ComponentManager->GetComponentType<T>(), false);
		m_EntityManager->SetSignature(entity, signature);

		m_SystemManager->OnEntitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& GetComponent(EntityID entity)
	{
		return m_ComponentManager->GetComponent<T>(entity);
	}

	template<typename T>
	ComponentID GetComponentType()
	{
		return m_ComponentManager->GetComponentType<T>();
	}

	template<typename T>
	std::shared_ptr<ComponentStorageSystem<T>> GetComponentStorage()
	{
		return m_ComponentManager->GetStorage<T>();
	}


	// System methods
	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		m_SystemManager->AddSystem<T>();
		return GetSystem<T>();
	}

	template<typename T>
	std::shared_ptr<T> GetSystem()
	{
		return m_SystemManager->GetSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(Signature signature)
	{
		m_SystemManager->SetSignature<T>(signature);
	}

private:
	std::unique_ptr<ComponentManager> m_ComponentManager;
	std::unique_ptr<EntityManager> m_EntityManager;
	std::unique_ptr<SystemManager> m_SystemManager;
};
