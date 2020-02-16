#include <iostream>

#include "FDC/DataSet.h"
#include "FDC/FunctionSet.h"

#include "NECS/KeyNode.h"
#include "NECS/StorageNode.h"

#include "Concepts/FunctionPointers.h"

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


void RunDCFCTest()
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


void RunNodeTest() 
{
	KeyNode keyNode;
	StorageNode<TransformData> transNode;
	StorageNode<LightData> lightNode;

	keyNode.messaging.Subscribe(&transNode);
	keyNode.messaging.Subscribe(&lightNode);
}

int main()
{
	RunVoidFuncPtrTest();
	RunParamFuncPtrTest();
	std::cin.get();
}