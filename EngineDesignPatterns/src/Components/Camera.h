#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Camera 
{
	glm::mat4 projectionMatrix;

	static glm::mat4 MakeProjectionTransform(float fov, float aspect, float nearClip, float farClip)
	{
		return glm::perspective(glm::radians(fov), aspect, nearClip, farClip);
	}
};