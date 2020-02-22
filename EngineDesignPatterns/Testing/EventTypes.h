#pragma once

struct CollisionEvent
{
	bool isColliding;
};

struct EntityDestroyedEvent
{
	EntityID id;
	bool handled;
};
