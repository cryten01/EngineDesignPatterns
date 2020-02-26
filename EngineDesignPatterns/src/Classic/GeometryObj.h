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

class GeometryObj
{
protected:
	GLuint _vao;
	GLuint _vbo;
	GLuint _vboNormals;
	GLuint _vboIndices;
	unsigned int _elements;

	Shader* shader;

	glm::mat4 _modelMatrix;
	glm::mat4 _transformMatrix;

	 GeometryObj(glm::mat4 modelMatrix, GeometryData& data);
	~GeometryObj();

	void draw(glm::mat4 matrix = glm::mat4(1.0f));
	void transform(glm::mat4 transformation);
	void setTransformMatrix(glm::mat4 transformMatrix);
	glm::mat4 getModelMatrix();
	glm::mat4 getTransformMatrix();
	void resetModelMatrix();

	static GeometryData createCubeGeometry(float width, float height, float depth);
};

