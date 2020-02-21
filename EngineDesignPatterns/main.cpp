#include <iostream>

#include "FDC/DataSet.h"
#include "FDC/FunctionSet.h"

#include "ECS/EntityManager.h"
#include "ECS/Component.h"
#include "ECS/ComponentStorage.h"
#include "ECS/ComponentManager.h"
#include "ECS/SystemManager.h"
#include "Event/Station.h"
#include "Event/StationTest.h"

#include "Concepts/FunctionPointers.h"
#include "Concepts/InheritanceByData.h"
#include "Concepts/InheritanceBySystem.h"
#include "Concepts/StaticCasting.h"


void RunFDCTest()
{
	// Game object Data
	Container dsContainer1;
	Container dsContainer2;

	// Game object Behavior
	FSContainer fsContainer1;	
	FSContainer fsContainer2;
	FSContainer fsContainer3;

	//TransformFS tfs;
	TransformFuncs tfs;
	fsContainer1.sets.AttachSet(fsContainer1, tfs);
	fsContainer1.sets.GetSet(fsContainer1, tfs);

	// Container Test
	TransformData td = fsContainer1.sets.CreateSet<TransformData>();
	LightData lds = fsContainer1.sets.CreateSet<LightData>();
	fsContainer1.sets.AttachSet(dsContainer1, td);
	fsContainer1.sets.AttachSet(dsContainer1, lds);
	fsContainer2.sets.GetSet(dsContainer1, td);
	fsContainer2.sets.GetSet(dsContainer1, lds);
	fsContainer2.sets.RemoveSet<TransformData>(dsContainer1);
	fsContainer2.sets.RemoveSet<LightData>(dsContainer1);
	bool check = fsContainer2.sets.HasSet<TransformData>(dsContainer1);

	// Messaging Test
	fsContainer1.messaging.Send({ fsContainer2.messaging }, dsContainer1);
	fsContainer2.messaging.Send({ fsContainer1.messaging, fsContainer3.messaging }, dsContainer2);
}


void RunDODEventTest()
{
	StationData<EntityEvent> station; 	// Subscribe to a system not data


	AType a;
	a.InitCallbacks();

	BType b;
	b.InitCallbacks();

	EntityEvent e;
	e.entity = 10;

	CollisionEvent c;
	c.isColliding = true;

	StationSystem::Publish(e);
	StationSystem::Publish(c);

	//StationSystem::Subscribe<EntityEvent>(btype.OnReceive);
	//StationSystem::Subscribe<EntityEvent>(atype.OnFoo);

	//StationSystem::Unsubscribe<EntityEvent>(btype.OnReceive);
}


void RunDODTest() 
{
	// Init systems
	SystemManager sysManager;

	sysManager.AddSystem<ComponentManagerSystem>();
	sysManager.AddSystem<EntityManagerSystem>();

	// Init data
	std::shared_ptr<ComponentManagerSystem> storageSys = sysManager.GetSystem<ComponentManagerSystem>();
	std::shared_ptr<EntityManagerSystem> entitySys = sysManager.GetSystem<EntityManagerSystem>();

	EntityID entity1 = entitySys->IssueEntity();
	EntityID entity2 = entitySys->IssueEntity();

	// Create test data
	storageSys->AddStorage<MeshData>();
	storageSys->AddStorage<TestData>();

	for (size_t i = 0; i < 20; i++)
	{
		MeshData data;
		data.x = i;
		data.y = i + 1;
		data.z = i + 2;
		storageSys->AddComponent<MeshData>(entity2, data);

		TestData t;
		t.y = 10;
		storageSys->AddComponent<TestData>(entity2, t);

		//data = storageSys->GetEntry<MeshData>(entity2);
		//std::cout << data.x << " " << data.y << " " << data.z << std::endl;
	}

	entitySys->ReturnEntity(entity2);
}

int main()
{
	RunDODTest();
	//RunDODEventTest();

	//RunVoidFuncPtrTest();
	//RunParamFuncPtrTest();

	//Casting();
	//InheritanceByData();
	//InheritanceByInterface();

	std::cin.get();
}