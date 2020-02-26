#include "CameraObj.h"

CameraObj::CameraObj(ViewFrustumDimensions dimensions)
	: m_FrustumDimensions(dimensions)
{
	// Initialize projection matrix
	CalculateProjectionMatrix();
}


void CameraObj::CalculateViewMatrix(glm::vec3 position, glm::vec3 lookTarget, glm::vec3 upDirection)
{
	// Make sure to reset matrix to identity matrix first
	m_ViewMatrix = glm::mat4(1.0);

	// No inversion needed because of lookAt function!
	m_ViewMatrix = glm::lookAt(position, lookTarget, upDirection);
}


void CameraObj::CalculateProjectionMatrix()
{
	ViewFrustumDimensions& dimensions = m_FrustumDimensions;

	m_ProjectionMatrix = glm::perspective(
		glm::radians(dimensions.fov),
		dimensions.aspect,
		dimensions.nearPlane,
		dimensions.farPlane
	);
}


void CameraObj::OnUpdate(float deltaTime)
{
	// Update members
	glm::vec3 localPosition = glm::vec3(0, 0, 10); // TODO
	glm::vec3 localFrontDirection = glm::vec3(0, 0, -1);
	glm::vec3 localUpDirection = glm::vec3(0, 1, 0);

	CalculateViewMatrix(localPosition, localPosition + localFrontDirection, localUpDirection);
	CalculateProjectionMatrix();

	// Submit uniform data
	shader->SetMat4("uProjection", m_ProjectionMatrix);
	shader->SetMat4("uView", m_ViewMatrix);
}