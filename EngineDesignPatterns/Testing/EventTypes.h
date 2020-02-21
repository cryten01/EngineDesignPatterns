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
