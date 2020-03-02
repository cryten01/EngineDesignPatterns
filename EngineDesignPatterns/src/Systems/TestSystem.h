#pragma once

#include "ECS/System.h"

class TestSystem : public System
{
public:
	void Init();
	void Update(float dt);
};


