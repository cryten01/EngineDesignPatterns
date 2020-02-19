#pragma once

#include "EntityComponent.h"

#include <set>

class System
{
public:
	std::set<Entity> mEntities;
};
