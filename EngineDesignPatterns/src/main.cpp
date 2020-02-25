
#include <random>
#include <chrono>
#include <iostream>

#include "ECS/Coordinator.h"
#include "Event/Station.h"
#include "Testing/EventTypes.h"
#include "Core/Window.h"

#include "Graphics/Shader.h"
#include "Graphics/GPULog.h"

#include "Systems/RenderSystem.h"

#include "Components/Camera.h"
#include "Components/Transform.h"
#include "Components/Renderable.h"

Coordinator gCoordinator; // necessary for extern

int main()
{
	GLFWwindow* window = Window::Create("EngineDesignPatterns", 1024, 768);

	GPULog::Init();

	gCoordinator.Init();

	gCoordinator.RegisterComponent<Transform>();
	gCoordinator.RegisterComponent<Camera>();
	gCoordinator.RegisterComponent<Renderable>();

	auto renderSystem = gCoordinator.RegisterSystem<RenderSystem>();
	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<Renderable>());
		signature.set(gCoordinator.GetComponentType<Transform>());
		gCoordinator.SetSystemSignature<RenderSystem>(signature);
	}

	renderSystem->Init();

	std::vector<EntityID> entities(10);

	std::default_random_engine generator;
	std::uniform_real_distribution<float> randPosition(-100.0f, 100.0f);
	std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
	std::uniform_real_distribution<float> randScale(3.0f, 5.0f);
	std::uniform_real_distribution<float> randColor(0.0f, 1.0f);
	std::uniform_real_distribution<float> randGravity(-10.0f, -1.0f);

	float scale = randScale(generator);

	for (auto& entity : entities)
	{
		entity = gCoordinator.CreateEntity();

		Transform t;
		t.position = glm::vec3(randPosition(generator), randPosition(generator), randPosition(generator));
		t.rotation = glm::vec3(randRotation(generator), randRotation(generator), randRotation(generator));
		t.scale = glm::vec3(scale, scale, scale);
		gCoordinator.AddComponent(entity, t);
	
		Renderable r;
		r.color = glm::vec3(randColor(generator), randColor(generator), randColor(generator));
		gCoordinator.AddComponent(entity, r);
	}



	float dt = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		auto startTime = std::chrono::high_resolution_clock::now();

		// Update systems here
		renderSystem->Update(dt);
		
		// Swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();

		auto stopTime = std::chrono::high_resolution_clock::now();

		dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
	}

	// Destroy framework
	Window::Destroy();
}