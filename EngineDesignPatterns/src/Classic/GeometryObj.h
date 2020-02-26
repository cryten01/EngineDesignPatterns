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

struct Physics
{
	glm::vec3 force;
	glm::vec3 velocity;
	glm::vec3 acceleration;
};


class GeometryObj
{
public:
	 GeometryObj(glm::mat4 modelMatrix, GeometryData& data, Physics& physics);
	~GeometryObj();

	void draw(glm::mat4 matrix = glm::mat4(1.0f));
	void transform(glm::mat4 transformation, float dt);
	void setTransformMatrix(glm::mat4 transformMatrix);
	glm::mat4 getModelMatrix();
	glm::mat4 getTransformMatrix();
	void resetModelMatrix();

	static GeometryData createCubeGeometry(float width, float height, float depth);

private:
	GLuint _vao;
	GLuint _vbo;
	GLuint _vboNormals;
	GLuint _vboIndices;
	unsigned int _elements;

	Shader* shader;

	glm::vec3 _color;
	glm::mat4 _modelMatrix;
	glm::mat4 _transformMatrix;

	Physics _physics;

	glm::vec3 _position; // TODO
};

