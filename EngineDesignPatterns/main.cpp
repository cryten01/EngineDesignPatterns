#include <iostream>

#include "FDC/DataSet.h"
#include "FDC/FunctionSet.h"

#include "DOD/Key.h"
#include "DOD/DataStorage.h"
#include "DOD/Register.h"
#include "DOD/PubSub.h"

#include "Concepts/FunctionPointers.h"
#include "Concepts/Inheritance.h"

/**
 *	Entity Component System (Separation Function/Data, Composition over inheritance, Save Multi Threading)
 *	Functional Programming (Immutability, Reduce Side effects, Save Multi Threading)
 *	Actor Model (Event Based, Save Multi Threading)
 */



 // Data types
 // Groups of different data types (0-n)

 // Function types
 // Groups of function types (0-n)

 // Separate isolated units

 // Node = Container of functionality that processes data, composed of other nodes
 // Message = Container of data that can be send across links
 // Connections = represented by the amount of node references each node has

 // Static methods are loaded during runtime (no loading control)


void RunFDCTest()
{
	//std::shared_ptr<TransformData> td = std::make_shared<TransformData>();

	// Simple Function Container  (no functions)
	// Base Function Container (basic functions)

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


bool OnReceive(TransformData data) 
{
	std::cout << "Received transform data" << std::endl;
	return true;
}

void RunDODTest() 
{
	KeyFactory factory;
	Key key1 = IssueKey(factory);
	Key key2 = IssueKey(factory);

	StorageRegister reg;
	AddStorage<TransformData>(reg);
	AddStorage<LightData>(reg);

	TransformData data;
	data.orientation = glm::vec3(0);
	data.position = glm::vec3(0);
	data.scale = glm::vec3(1);

	MakeEntry<TransformData>(reg, key1, data);
	MakeEntry<TransformData>(reg, key2, data);
	GetEntry<TransformData>(reg, key1);
	ClearEntry<TransformData>(reg, key1);


	// Subscribe to a system not data
	Station<TransformData> tConn;
	Subscribe(tConn, OnReceive);
	Publish(tConn, data);
	Unsubscribe(tConn, OnReceive);

	std::shared_ptr<DataStorage> st1 = std::make_shared<TStorage<int>>();
	std::static_pointer_cast<TStorage<int>>(st1)->storageMap;

	std::shared_ptr<DataStorage> st2 = std::make_shared<TStorage<float>>();
}

int main()
{
	//RunDODTest();
	//RunVoidFuncPtrTest();
	//RunParamFuncPtrTest();

	InheritanceByElement();
	//InheritanceByInterface();

	std::cin.get();
}