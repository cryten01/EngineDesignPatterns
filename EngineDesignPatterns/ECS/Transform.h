#pragma once

// Data
struct TransformData : Component
{
	float x, y, z;
};

// Functional behavior
class TransformSystem
{
public:
	static void ChangePosition(TransformData& data) 
	{
		data.x = 10;
		data.y = 10;
		data.z = 10;
	}
};