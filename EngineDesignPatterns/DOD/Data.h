#pragma once

struct Data 
{};


struct CollisionEvent : Data 
{
	bool isColliding;
};

struct EntityEvent : Data 
{
	Entity entity;
	bool handled;
};


struct TestData : Data 
{
	int y;
};

struct MeshData : Data
{
	float x, y, z;
};