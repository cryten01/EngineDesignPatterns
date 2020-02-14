#pragma once

struct Input
{
	bool isPressed = false;
	int keycode = 0;
};

struct Position
{
	float x = 0;
	float y = 0;
	float z = 0;
};

struct Velocity
{
	float y = 0;
};

struct Recepient
{
};

struct DataContainer
{
	bool active = true;
	Input i;
	Position p;
	Velocity v;
	std::vector<Recepient> r;
};
