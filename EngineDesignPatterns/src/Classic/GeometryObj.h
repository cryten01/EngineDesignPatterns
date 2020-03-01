#pragma once

#include <glad/glad.h>
#include <vector>
#include <glm\gtc\matrix_transform.hpp>

#include "Graphics/Shader.h"


struct GeometryData 
{
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;
};

struct PhysicsObj
{
	glm::vec3 force;
	glm::vec3 velocity;
	glm::vec3 acceleration;
};

struct TransformObj
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};


class GeometryObj
{
public:
	 GeometryObj(GeometryData data, PhysicsObj physics, glm::vec3 color, TransformObj transform, std::shared_ptr<Shader> shader);
	~GeometryObj();

	void OnUpdate(float dt);

	static GeometryData createCubeGeometry(float width, float height, float depth);

private:
	GLuint m_Vao;
	GLuint m_Vbo;
	GLuint m_VboNormals;
	GLuint m_VboIndices;
	unsigned int m_Elements;

	TransformObj m_Transform;
	PhysicsObj m_Physics;
	glm::vec3 m_Color;

	std::shared_ptr<Shader> m_Shader;
};

