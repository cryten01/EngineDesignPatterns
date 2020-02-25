
#include <random>
#include <chrono>
#include <iostream>

#include "Concepts/FunctionPointers.h"
#include "Concepts/InheritanceByData.h"
#include "Concepts/InheritanceBySystem.h"
#include "Concepts/StaticCasting.h"

#include "ECS/Coordinator.h"
#include "Event/Station.h"
#include "Testing/ComponentTypes.h"
#include "Testing/EventTypes.h"
#include "Testing/TestSystem.h"
#include "Core/Window.h"
#include "Graphics/Shader.h"
#include "Graphics/GPULog.h"


Coordinator gCoordinator; // necessary for extern


void InitECS()
{
	gCoordinator.Init();

	gCoordinator.RegisterComponent<MeshComponent>();
	gCoordinator.RegisterComponent<SpeedComponent>();

	gCoordinator.RegisterSystem<TestSystem>();
	auto testSystem = gCoordinator.GetSystem<TestSystem>();

	Signature signature;
	signature.set(gCoordinator.GetComponentType<MeshComponent>());
	signature.set(gCoordinator.GetComponentType<SpeedComponent>());
	gCoordinator.SetSystemSignature<TestSystem>(signature);

	std::vector<EntityID> entities(10);

	std::default_random_engine generator;
	std::uniform_real_distribution<float> randCoords(-100.0f, 100.0f);
	std::uniform_real_distribution<float> randSpeed(0.0f, 3.0f);

	for (auto& entity : entities)
	{
		entity = gCoordinator.CreateEntity();
		gCoordinator.AddComponent(entity, MeshComponent{ 1.0f, randCoords(generator), randCoords(generator) });
		gCoordinator.AddComponent(entity, SpeedComponent{ randSpeed(generator) });
		gCoordinator.DestroyEntity(entity);
	}
}

int main()
{
	GLFWwindow* window = Window::Create("EngineDesignPatterns", 800, 600);
	
	GPULog::Init();

	InitECS();

	Shader shader("assets/shaders/flatColor.vert", "assets/shaders/flatColor.frag");

	float dt = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		auto startTime = std::chrono::high_resolution_clock::now();

		// Process input here

		// Render
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();

		auto stopTime = std::chrono::high_resolution_clock::now();

		dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
	}

	Window::Destroy();
}