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
	void CreateCube();
	glm::mat4 MakeProjectionTransform(float fov, float aspect, float nearClip, float farClip);

private:
	std::unique_ptr<Shader> shader;
	EntityID mCamera;

	GLuint mVao{};
	GLuint mVboVertices{};
	GLuint mVboNormals{};
};

