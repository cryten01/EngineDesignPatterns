#pragma once



struct CollisionEvent 
{
	bool isColliding;
};

struct EntityEvent 
{
	EntityID entity;
	bool handled;
};


struct TestData 
{
	int y;
};

struct MeshData
{
	float x, y, z;
};