#include "RenderSystem.h"
#include "Graphics/Shader.h"
#include "ECS/Coordinator.h"

extern Coordinator gCoordinator;

void RenderSystem::Init()
{
	// Create default shader
	shader = std::make_unique<Shader>("assets/shaders/flatColor.vert", "assets/shaders/flatColor.frag");

	// Create camera entity
	mCamera = gCoordinator.CreateEntity();

	// Attach camera components

}

void RenderSystem::Update(float dt)
{
	// Clear window first
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
