#pragma once

#include "DCS.h"
#include <vector>

// Data
struct MeshData : DataSet
{
	std::vector<float> points;
};

// Functional behavior
class MeshSystem : FunctionSet
{
public:
	void ChangePointAt(MeshData& data)
	{
		data.points.at(0) = 100;
	}
};