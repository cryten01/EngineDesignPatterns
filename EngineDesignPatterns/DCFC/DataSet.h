#pragma once

#include <glm/glm.hpp>

struct DataSet
{
	size_t id;
	size_t tHash;
	const char* tName;
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


/**
 * A generic data set container that can be passed between different function container.
 */
struct DSContainer
{
	std::vector<DataSet*> sets;
};
