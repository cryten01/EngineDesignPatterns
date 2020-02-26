#pragma once

#include <glad/glad.h>
#include <memory>

#include "Graphics/Shader.h"
#include "ECS/System.h"
#include "ECS/ECS.h"

class RenderSystem : public System
{
public:
	void Init();
	void Update(float dt);

	void CreateCube(float width, float height, float depth);

	glm::mat4 CalculateProjectionTransform(float fov, float aspect, float nearClip, float farClip);

private:
	std::unique_ptr<Shader> shader;
	EntityID mCamera;

	GLuint mVao{};
	GLuint mVboIndices{};
	GLuint mVboVertices{};
	GLuint mVboNormals{};
	GLuint mElementCount = 0;
};

