#include <iostream>

#include "System.h"
#include "Transform.h"
#include "Mesh.h"


int main()
{
	Entity entity;
	TransformData transData1;
	TransformData transData2;
	MeshData meshData;


	meshData.points.push_back(2);
	meshData.points.push_back(3);
	meshData.points.push_back(5);
	transData1.x = 2;
	transData1.y = 2;
	transData1.z = 2;
	transData2.x = 3;
	transData2.y = 4;
	transData2.z = 5;


	System::AddData<TransformData>(transData1, entity.dataList);
	System::AddData<TransformData>(transData2, entity.dataList);
	System::AddData<MeshData>(meshData, entity.dataList);


	TransformData transform = System::GetData<TransformData>(entity.dataList);
	std::vector<TransformData> transform2 = System::GetAllData<TransformData>(entity.dataList);
	MeshData mesh = System::GetData<MeshData>(entity.dataList);


	std::cout << System::HasData<MeshData>(entity.dataList) << std::endl;
	std::cout << transform.x << std::endl;
	std::cout << transform2.at(1).y << std::endl;
	std::cin.get();
}