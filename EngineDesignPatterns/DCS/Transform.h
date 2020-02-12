#pragma once

// Data
struct TransformData : Data
{
	float x, y, z;
};

// Functional behavior
class TransformSystem : System
{
public:
	void ChangePosition(TransformData& data) 
	{
		data.x = 10;
		data.y = 10;
		data.z = 10;
	}
};