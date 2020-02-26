#pragma once

#include "Graphics/Shader.h"
#include <glm\gtc\matrix_transform.hpp>

struct ViewFrustumDimensions
{
	float fov;
	float aspect;
	float nearPlane;
	float farPlane;
};

class CameraObj
{
	 CameraObj(ViewFrustumDimensions dimensions);
	~CameraObj() = default;

	const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
	const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }


	void OnUpdate(float deltaTime);

private:
	void CalculateProjectionMatrix();
	void CalculateViewMatrix(glm::vec3 position, glm::vec3 frontDirection, glm::vec3 upDirection);

	ViewFrustumDimensions m_FrustumDimensions;

	glm::vec3 m_LookTarget = glm::vec3(0.0);
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;

	Shader* shader;
};

