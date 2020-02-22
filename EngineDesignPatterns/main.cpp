#include <iostream>
#include <random>
#include <chrono>

#include "Concepts/FunctionPointers.h"
#include "Concepts/InheritanceByData.h"
#include "Concepts/InheritanceBySystem.h"
#include "Concepts/StaticCasting.h"

#include "ECS/Coordinator.h"
#include "Event/Station.h"
#include "Testing/ComponentTypes.h"
#include "Testing/EventTypes.h"
#include "Testing/TestSystem.h"


Coordinator coordinator; // necessary for extern

void RunEventTest()
{
	//StationData<EntityEvent> station; 	// Subscribe to a system not data

	//AType a;
	//a.InitCallbacks();

	//BType b;
	//b.InitCallbacks();

	//EntityEvent e;
	//e.entity = 10;

	//CollisionEvent c;
	//c.isColliding = true;

	//StationSystem::Publish(e);
	//StationSystem::Publish(c);

	//StationSystem::Subscribe<EntityEvent>(btype.OnReceive);
	//StationSystem::Subscribe<EntityEvent>(atype.OnFoo);
	//StationSystem::Unsubscribe<EntityEvent>(btype.OnReceive);
}

void RunECSTest()
{
	coordinator.Init();

	coordinator.RegisterComponent<MeshComponent>();
	coordinator.RegisterComponent<SpeedComponent>();

	coordinator.RegisterSystem<TestSystem>();
	auto testSystem = coordinator.GetSystem<TestSystem>();

	Signature signature;
	signature.set(coordinator.GetComponentType<MeshComponent>());
	signature.set(coordinator.GetComponentType<SpeedComponent>());
	coordinator.SetSystemSignature<TestSystem>(signature);

	std::vector<EntityID> entities(MAX_ENTITIES);

	std::default_random_engine generator;
	std::uniform_real_distribution<float> randCoords(-100.0f, 100.0f);
	std::uniform_real_distribution<float> randSpeed(0.0f, 3.0f);


	for (size_t i = 0; i < 2; i++)
	{
		EntityID entity = coordinator.CreateEntity();
		coordinator.AddComponent(entity, MeshComponent{ 1.0f, randCoords(generator), randCoords(generator) });
		coordinator.AddComponent(entity, SpeedComponent{ randSpeed(generator) });
		coordinator.DestroyEntity(entity);
	}


	//for (auto& entity : entities)
	//{
	//	entity = coordinator.CreateEntity();
	//	coordinator.AddComponent(entity, MeshComponent{ 1.0f, randCoords(generator), randCoords(generator) });
	//	coordinator.AddComponent(entity, SpeedComponent{ randSpeed(generator) });
	//	coordinator.DestroyEntity(entity);
	//}

	//float dt = 0.0f;

	//while (true)
	//{
	//	auto startTime = std::chrono::high_resolution_clock::now();

	//	testSystem->Update(dt);

	//	auto stopTime = std::chrono::high_resolution_clock::now();

	//	dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
	//}
}

int main()
{
	RunECSTest();
	std::cin.get();
}