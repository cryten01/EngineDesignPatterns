#include "GeometryObj.h"


GeometryObj::GeometryObj(GeometryData data, PhysicsObj physics, glm::vec3 color, TransformObj transform, std::shared_ptr<Shader> shader)
	: _elements(data.indices.size()), _physics(physics), _color(color), _transform(transform), _shader(shader)
{
	// create VAO
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	// create positions VBO
	glGenBuffers(1, &_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, data.positions.size() * sizeof(glm::vec3), data.positions.data(), GL_STATIC_DRAW);
	// bind positions to location 0
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// create normals VBO
	glGenBuffers(1, &_vboNormals);
	glBindBuffer(GL_ARRAY_BUFFER, _vboNormals);
	glBufferData(GL_ARRAY_BUFFER, data.normals.size() * sizeof(glm::vec3), data.normals.data(), GL_STATIC_DRAW);
	// bind normals to location 1
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// create and bind indices VBO
	glGenBuffers(1, &_vboIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vboIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.indices.size() * sizeof(unsigned int), data.indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GeometryObj::~GeometryObj()
{
	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_vboNormals);
	glDeleteBuffers(1, &_vboIndices);
	glDeleteVertexArrays(1, &_vao);
}

void GeometryObj::OnUpdate(float dt)
{
	// Update position
	_transform._position += _physics.velocity * dt;

	// Update velocity
	_physics.velocity += _physics.force * dt;

	// Update modelMatrix
	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), _transform._position);
	//modelMatrix = glm::rotate(modelMatrix, _transform._rotation.y, glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, _transform._scale);

	// Set uniforms
	_shader->SetVec3("uColor", _color);
	_shader->SetMat4("uModel", modelMatrix);

	// Draw geometry
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _elements, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

GeometryData GeometryObj::createCubeGeometry(float width, float height, float depth)
{
	GeometryData data;

	data.positions = {
		// front
		glm::vec3(-width / 2.0f, -height / 2.0f,  depth / 2.0f),
		glm::vec3(width / 2.0f, -height / 2.0f,  depth / 2.0f),
		glm::vec3(width / 2.0f, height / 2.0f,  depth / 2.0f),
		glm::vec3(-width / 2.0f, height / 2.0f,  depth / 2.0f),
		// back
		glm::vec3(width / 2.0f, -height / 2.0f,  -depth / 2.0f),
		glm::vec3(-width / 2.0f, -height / 2.0f,  -depth / 2.0f),
		glm::vec3(-width / 2.0f, height / 2.0f,  -depth / 2.0f),
		glm::vec3(width / 2.0f, height / 2.0f,  -depth / 2.0f),
		// right
		glm::vec3(width / 2.0f, -height / 2.0f,  depth / 2.0f),
		glm::vec3(width / 2.0f, -height / 2.0f,  -depth / 2.0f),
		glm::vec3(width / 2.0f, height / 2.0f,  -depth / 2.0f),
		glm::vec3(width / 2.0f, height / 2.0f,  depth / 2.0f),
		// left
		glm::vec3(-width / 2.0f, -height / 2.0f,  -depth / 2.0f),
		glm::vec3(-width / 2.0f, -height / 2.0f,  depth / 2.0f),
		glm::vec3(-width / 2.0f, height / 2.0f,  depth / 2.0f),
		glm::vec3(-width / 2.0f, height / 2.0f,  -depth / 2.0f),
		// top
		glm::vec3(-width / 2.0f, height / 2.0f,  -depth / 2.0f),
		glm::vec3(-width / 2.0f, height / 2.0f,  depth / 2.0f),
		glm::vec3(width / 2.0f, height / 2.0f,  depth / 2.0f),
		glm::vec3(width / 2.0f, height / 2.0f,  -depth / 2.0f),
		// bottom
		glm::vec3(-width / 2.0f, -height / 2.0f,  -depth / 2.0f),
		glm::vec3(width / 2.0f, -height / 2.0f,  -depth / 2.0f),
		glm::vec3(width / 2.0f, -height / 2.0f,  depth / 2.0f),
		glm::vec3(-width / 2.0f, -height / 2.0f,  depth / 2.0f)
	};

	data.normals = {
		// front
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, 1),
		glm::vec3(0, 0, 1),
		// back
		glm::vec3(0, 0, -1),
		glm::vec3(0, 0, -1),
		glm::vec3(0, 0, -1),
		glm::vec3(0, 0, -1),
		// right
		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 0),
		// left
		glm::vec3(-1, 0, 0),
		glm::vec3(-1, 0, 0),
		glm::vec3(-1, 0, 0),
		glm::vec3(-1, 0, 0),
		// top
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 0),
		// bottom
		glm::vec3(0, -1, 0),
		glm::vec3(0, -1, 0),
		glm::vec3(0, -1, 0),
		glm::vec3(0, -1, 0)
	};


	data.indices = {
		// front
		0, 1, 2,
		2, 3, 0,
		// back
		4, 5, 6,
		6, 7, 4,
		// right
		8, 9, 10,
		10, 11, 8,
		// left
		12, 13, 14,
		14, 15, 12,
		// top
		16, 17, 18,
		18, 19, 16,
		// bottom
		20, 21, 22,
		22, 23, 20
	};

	return std::move(data);
}