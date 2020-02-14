#include <iostream>

#include "DCS/DCS.h"
#include "DCS/Transform.h"
#include "DCS/Mesh.h"
#include "DCS/Container.h"
#include "DCS/Element.h"


#include "DCFC/DataSet.h"
#include "DCFC/FunctionSet.h"


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


void RunDCSTest()
{
	ContainerSystem		containerSystem;
	Container			container;


	SampleSystem tsys;
	MeshSystem msys;



	TransformData transData1;
	transData1.x = 2;
	transData1.y = 2;
	transData1.z = 2;

	TransformData transData2;
	transData2.x = 3;
	transData2.y = 4;
	transData2.z = 5;

	MeshData meshData;
	meshData.points.push_back(2);
	meshData.points.push_back(3);
	meshData.points.push_back(5);


	containerSystem.AddElement(transData1, container.data);
	containerSystem.AddElement(transData2, container.data);
	containerSystem.AddElement(meshData, container.data);

	TransformData transform = containerSystem.GetElement<TransformData>(container.data);
	std::vector<TransformData> transform2 = containerSystem.GetAllElements<TransformData>(container.data);
	MeshData mesh = containerSystem.GetElement<MeshData>(container.data);

	std::cout << mesh.points.at(0) << std::endl;
	std::cout << transform.x << std::endl;
	std::cout << transform2.at(1).y << std::endl;
	std::cin.get();
}



void RunNodeTest()
{
	//TransformNode node1;
	//TransformNode node2;
	//MaterialNode node3;

	//node1.Data.active = true;

	//node1.Connect(node2);
	//node1.Send(node1.Data);
	//node1.Connect(node3);
	//node1.Send(node2.Data);


}


void RunDCFCTest()
{
	//std::shared_ptr<TransformData> td = std::make_shared<TransformData>();

	// Game object Data
	DSContainer dsContainer1;	
	DSContainer dsContainer2;

	// Game object Behavior
	FSContainer fsContainer1;	
	FSContainer fsContainer2;
	FSContainer fsContainer3;


	TransformFS tfs;
	fsContainer1.set.AttachSet(fsContainer1, tfs);
	fsContainer1.set.GetSet(fsContainer1, tfs);


	// Container Test
	TransformDS td = fsContainer1.set.CreateSet<TransformDS>();
	LightDS lds = fsContainer1.set.CreateSet<LightDS>();
	fsContainer1.set.AttachSet(dsContainer1, td);
	fsContainer1.set.AttachSet(dsContainer1, lds);
	fsContainer2.set.GetSet(dsContainer1, td);
	fsContainer2.set.GetSet(dsContainer1, lds);
	fsContainer2.set.RemoveSet<DSContainer, TransformDS>(dsContainer1);
	fsContainer2.set.RemoveSet<DSContainer, LightDS>(dsContainer1);
	bool check = fsContainer2.set.HasSet<DSContainer, TransformDS>(dsContainer1);

	// Messaging Test
	fsContainer1.messaging.Send({ fsContainer2.messaging }, dsContainer1);
	fsContainer2.messaging.Send({ fsContainer1.messaging, fsContainer3.messaging }, dsContainer2);
}

int main()
{
	RunDCFCTest();
	std::cin.get();
}