#pragma once

#include "DCS.h"
#include <vector>

// Data
struct MeshData : Data
{
	std::vector<float> points;
};

// Functional behavior
class MeshSystem : Function
{
public:
	void ChangePointAt(MeshData& data)
	{
		data.points.at(0) = 100;
	}
};