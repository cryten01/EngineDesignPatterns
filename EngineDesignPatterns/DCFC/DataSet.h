#pragma once

#include <glm/glm.hpp>

struct DataSet
{
	size_t hash;
	const char* name;
};

struct TransformDS : DataSet
{
	glm::vec3 position = glm::vec3(0);
	glm::vec3 orientation = glm::vec3(0);
	glm::vec3 scale = glm::vec3(0);
	float velocity = 0.0f;
};

struct LightDS : DataSet
{
	glm::vec3 color;
	glm::vec3 direction;
	glm::vec3 attenuation;
};

struct KeyInputDS : DataSet
{
	bool isPressed = false;
	int keycode = 0;
};


struct DSContainer
{
	std::vector<DataSet*> dataSets;
};
