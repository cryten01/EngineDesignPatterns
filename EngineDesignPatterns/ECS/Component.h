#pragma once

struct Component
{};


struct CollisionEvent : Component 
{
	bool isColliding;
};

struct EntityEvent : Component 
{
	EntityID entity;
	bool handled;
};


struct TestData : Component 
{
	int y;
};

struct MeshData : Component
{
	float x, y, z;
};