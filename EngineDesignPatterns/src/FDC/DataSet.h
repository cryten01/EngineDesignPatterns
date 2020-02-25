#pragma once

#include <glm/glm.hpp>
#include "FDC/DCFC.h"

struct TransformData : Set
{
	glm::vec3 position = glm::vec3(0);
	glm::vec3 orientation = glm::vec3(0);
	glm::vec3 scale = glm::vec3(0);
	float velocity = 0.0f;
};

struct LightData : Set
{
	glm::vec3 color;
	glm::vec3 direction;
	glm::vec3 attenuation;
};

struct entityInputData : Set
{
	bool isPressed = false;
	int entitycode = 0;
};



