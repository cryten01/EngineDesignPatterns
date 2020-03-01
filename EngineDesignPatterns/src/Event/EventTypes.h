#pragma once

struct CollisionEvent
{
	bool isColliding;
};

struct EntityDestroyedEvent
{
	EntityID id;
};

struct LayerEvent 
{};
