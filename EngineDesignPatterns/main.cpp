#include <iostream>

#include "FDC/DataSet.h"
#include "FDC/FunctionSet.h"

#include "DOD/EntityFactory.h"
#include "DOD/Data.h"
#include "DOD/Storage.h"
#include "DOD/StorageRegister.h"
#include "DOD/SystemRegister.h"
#include "DOD/Station.h"
#include "DOD/StationTest.h"

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

	EntityEvent e;
	e.entity = 10;

	AType atype;
	BType btype;

	atype.Subscribe();
	btype.Subscribe();

	StationSystem::Publish(EntityEvent());

	//StationSystem::Subscribe<EntityEvent>(btype.OnReceive);
	//StationSystem::Subscribe<EntityEvent>(atype.OnFoo);
	//StationSystem::Publish(e);
	//StationSystem::Unsubscribe<EntityEvent>(btype.OnReceive);
}


void RunDODTest() 
{
	EntityFactoryData factory;

	// Init systems
	SystemRegister::Add<StorageRegister>();
	SystemRegister::Add<EntityFactorySystem>();

	// Init data
	std::shared_ptr<StorageRegister> storageSys = SystemRegister::Get<StorageRegister>();
	std::shared_ptr<EntityFactorySystem> entitySys = SystemRegister::Get<EntityFactorySystem>();

	Entity entity1 = entitySys->IssueEntity(factory);
	Entity entity2 = entitySys->IssueEntity(factory);

	// Create test data
	storageSys->AddStorage<MeshData>();

	for (size_t i = 0; i < 20; i++)
	{
		MeshData data;
		data.x = i;
		data.y = i + 1;
		data.z = i + 2;

		storageSys->MakeEntry<MeshData>(entity1, data);
		data = storageSys->GetEntry<MeshData>(entity1);

		std::cout << data.x << " " << data.y << " " << data.z << std::endl;
	}
}

int main()
{
	RunDODTest();
	RunDODEventTest();

	//RunVoidFuncPtrTest();
	//RunParamFuncPtrTest();

	//Casting();
	//InheritanceByData();
	//InheritanceByInterface();

	std::cin.get();
}