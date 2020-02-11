#pragma once

#include "System.h"
#include <vector>

// Data
struct MeshData : Component
{
	std::vector<float> points;
};

// Functional behavior
class MeshSystem
{
public:
	static void ChangePointAt(MeshData& data)
	{
		data.points.at(0) = 100;
	}
};