#pragma once

// Data
struct TransformData : DataSet
{
	float x, y, z;
};

// Functional behavior (enables function injection)
// Modification only locally (= all inputs/outputs are not allowed to be modified)
// Data is not allowed to be mutated from multiple people at the same time
struct SampleSystem : FunctionSet
{
	void SingleMutation(TransformData& copy)
	{
		copy.x = 10;
		copy.y = 10;
		copy.z = 10;
	}

	void MultiMutation(float& x, float& y, float& z)
	{
		x = 10;
		y = 20;
		z = 20;
	}
};