#include <iostream>

#include "DCS/DCS.h"
#include "DCS/Transform.h"
#include "DCS/Mesh.h"
#include "DCS/Data.h"

#include "Node/Node.h"


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
	DataSystem dataSystem;
	DataContainer container;

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


	dataSystem.AddData<TransformData>(transData1, container.dataList);
	dataSystem.AddData<TransformData>(transData2, container.dataList);
	dataSystem.AddData<MeshData>(meshData, container.dataList);

	TransformData transform = dataSystem.GetData<TransformData>(container.dataList);
	std::vector<TransformData> transform2 = dataSystem.GetAllData<TransformData>(container.dataList);
	MeshData mesh = dataSystem.GetData<MeshData>(container.dataList);

	std::cout << dataSystem.HasData<MeshData>(container.dataList) << std::endl;
	std::cout << transform.x << std::endl;
	std::cout << transform2.at(1).y << std::endl;
	std::cin.get();
}


int main()
{
	RunDCSTest();
}