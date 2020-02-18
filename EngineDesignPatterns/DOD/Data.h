#pragma once

struct Data 
{};


struct KeyEvent : Data 
{
	Key key;
	bool handled;
};

struct MeshData : Data
{
	float x, y, z;
};