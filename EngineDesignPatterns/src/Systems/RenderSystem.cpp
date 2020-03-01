#include "RenderSystem.h"
#include "Graphics/Shader.h"
#include "ECS/Coordinator.h"
#include "Components/Transform.h"
#include "Components/Camera.h"
#include "Components/Renderable.h"

extern Coordinator gCoordinator;

void RenderSystem::Init()
{
	// Set GL defaults here
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Create default shader
	shader = std::make_unique<Shader>("assets/shaders/flatColor.vert", "assets/shaders/flatColor.frag");

	// Create camera entity
	mCamera = gCoordinator.CreateEntity();

	// Attach components
	Transform transform;
	transform.position = glm::vec3(0.0f, 0.0f, 250.0f);
	gCoordinator.AddComponent(mCamera, transform);

	Camera camera;
	camera.projectionMatrix = CalculateProjectionTransform(45.0f, 1024 / 768, 0.1f, 1000.0f);
	gCoordinator.AddComponent(mCamera, camera);

	// Create cube shape
	CreateCube(1,1,1);
}

void RenderSystem::Update(float dt)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->Use();
	glBindVertexArray(mVao);

	auto& cameraTransform = gCoordinator.GetComponent<Transform>(mCamera);
	auto& camera = gCoordinator.GetComponent<Camera>(mCamera);

	// Calculate view/projection matrix once per frame
	glm::mat4 viewMatrix = glm::lookAt(cameraTransform.position, glm::vec3(0), glm::vec3(0, 1, 0));
	glm::mat4 projectionMatrix = camera.projectionMatrix;

	// Get storage references once per frame
	auto transformStorage = gCoordinator.GetComponentStorage<Transform>();
	auto renderableStorage = gCoordinator.GetComponentStorage<Renderable>();

	for (auto entity : m_Entities)
	{
		auto const& transform = transformStorage->GetEntry(entity);
		auto const& renderable = renderableStorage->GetEntry(entity);

		glm::mat4 modelMatrix = glm::mat4(1.0);
		modelMatrix = glm::translate(modelMatrix, transform.position);
		modelMatrix = glm::rotate(modelMatrix, transform.rotation.y, glm::vec3(0, 1, 0)); // Note: Represents an expensive operation!
		modelMatrix = glm::scale(modelMatrix, transform.scale);

		shader->SetMat4("uModel", modelMatrix);
		shader->SetMat4("uView", viewMatrix);
		shader->SetMat4("uProjection", projectionMatrix);
		shader->SetVec3("uColor", renderable.color);

		glDrawElements(GL_TRIANGLES, mElementCount, GL_UNSIGNED_INT, NULL);
	}

	glBindVertexArray(0);
}


void RenderSystem::CreateCube(float width, float height, float depth)
{
	std::vector<glm::vec3> positions = {
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

	std::vector<glm::vec3> normals = {
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

	std::vector<GLuint> indices = {
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

	mElementCount = indices.size();

	// Create VAO
	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);

	// Create positions VBO
	glGenBuffers(1, &mVboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, mVboVertices);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_STATIC_DRAW);
	// Bind positions to location 0
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Create normals VBO
	glGenBuffers(1, &mVboNormals);
	glBindBuffer(GL_ARRAY_BUFFER, mVboNormals);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
	// Bind normals to location 1
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Create and bind indices VBO
	glGenBuffers(1, &mVboIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVboIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	// Unbind VAO
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

glm::mat4 RenderSystem::CalculateProjectionTransform(float fov, float aspect, float nearClip, float farClip)
{
	// Make sure to reset matrix to identity matrix first
	glm::mat4 viewMatrix = glm::mat4(1.0);

	viewMatrix = glm::perspective(glm::radians(fov), aspect, nearClip, farClip);

	return viewMatrix;
}
