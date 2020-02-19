#pragma once

struct Data 
{};


struct EntityEvent : Data 
{
	Entity entity;
	bool handled;
};

struct MeshData : Data
{
	float x, y, z;
};