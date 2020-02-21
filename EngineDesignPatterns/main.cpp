#include <iostream>

#include "Concepts/FunctionPointers.h"
#include "Concepts/InheritanceByData.h"
#include "Concepts/InheritanceBySystem.h"
#include "Concepts/StaticCasting.h"

#include "ECS/Coordinator.h"
#include "Event/Station.h"
#include "Testing/ComponentTypes.h"
#include "Testing/EventTypes.h"

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
}

int main()
{
	RunECSTest();
	//RunEventTest();
	std::cin.get();
}