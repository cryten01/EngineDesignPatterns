#include "PhysicsSystem.h"


#include "Components/Gravity.h"
#include "Components/RigidBody.h"
#include "Components/Transform.h"
#include "ECS/Coordinator.h"


extern Coordinator gCoordinator;


void PhysicsSystem::Init()
{
}

void PhysicsSystem::Update(float dt)
{
	auto rigidBodyStorage = gCoordinator.GetComponentStorage<RigidBody>();
	auto transformStorage = gCoordinator.GetComponentStorage<Transform>();
	auto gravityStorage = gCoordinator.GetComponentStorage<Gravity>();

	for (auto entity : m_Entities)
	{
		auto& rigidBody = rigidBodyStorage->GetEntry(entity);
		auto& transform = transformStorage->GetEntry(entity);
		auto& gravity = gravityStorage->GetEntry(entity);

		// Forces
		transform.position += rigidBody.velocity * dt;
		rigidBody.velocity += gravity.force * dt;
	}
}