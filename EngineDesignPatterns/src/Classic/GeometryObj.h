#pragma once

#include "Graphics/Shader.h"
#include <glad/glad.h>
#include <vector>
#include <glm\gtc\matrix_transform.hpp>

struct GeometryData {
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
	glm::vec3 _position;
	glm::vec3 _rotation;
	glm::vec3 _scale;
};


class GeometryObj
{
public:
	 GeometryObj(GeometryData& data, PhysicsObj& physics, glm::vec3 color, TransformObj& transform, std::shared_ptr<Shader> shader);
	~GeometryObj();

	void OnUpdate(float dt);

	static GeometryData createCubeGeometry(float width, float height, float depth);

private:
	GLuint _vao;
	GLuint _vbo;
	GLuint _vboNormals;
	GLuint _vboIndices;
	unsigned int _elements;

	glm::vec3 _color;

	TransformObj _transform;
	PhysicsObj _physics;

	std::shared_ptr<Shader> _shader;
};

