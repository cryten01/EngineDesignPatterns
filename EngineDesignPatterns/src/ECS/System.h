#pragma once

#include <set>

#include "ECS/ECS.h"

struct System
{
	// A set of entities registered for this system
	// Gets modified when OnEntityDestroyed() or OnEntitySignatureChanged() is called
	std::set<EntityID> m_Entities;
};