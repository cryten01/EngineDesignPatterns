
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
#include "Systems/PhysicsSystem.h"

#include "Components/Gravity.h"
#include "Components/Rigidbody.h"
#include "Components/Camera.h"
#include "Components/Transform.h"
#include "Components/Thrust.h"
#include "Components/Renderable.h"

Coordinator gCoordinator; // necessary for extern

int main()
{
	GLFWwindow* window = Window::Create("EngineDesignPatterns", 1024, 768);

	GPULog::Init();

	gCoordinator.Init();

	gCoordinator.RegisterComponent<Gravity>();
	gCoordinator.RegisterComponent<RigidBody>();
	gCoordinator.RegisterComponent<Thrust>();
	gCoordinator.RegisterComponent<Renderable>();
	gCoordinator.RegisterComponent<Transform>();
	gCoordinator.RegisterComponent<Camera>();

	auto physicsSystem = gCoordinator.RegisterSystem<PhysicsSystem>();
	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<Gravity>());
		signature.set(gCoordinator.GetComponentType<RigidBody>());
		signature.set(gCoordinator.GetComponentType<Transform>());
		gCoordinator.SetSystemSignature<PhysicsSystem>(signature);
	}

	physicsSystem->Init();


	auto renderSystem = gCoordinator.RegisterSystem<RenderSystem>();
	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<Renderable>());
		signature.set(gCoordinator.GetComponentType<Transform>());
		gCoordinator.SetSystemSignature<RenderSystem>(signature);
	}

	renderSystem->Init();


	std::vector<EntityID> entities(500);

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

		Gravity gravity;
		gravity.force = glm::vec3(0.0f, randGravity(generator), 0.0f);
		gCoordinator.AddComponent<Gravity>(entity, gravity);

		RigidBody rigidbody;
		rigidbody.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		rigidbody.acceleration = glm::vec3(0.0f, 0.0f, 0.0f);
		gCoordinator.AddComponent(entity, rigidbody);

		Transform transform;
		transform.position = glm::vec3(randPosition(generator), randPosition(generator), randPosition(generator));
		transform.rotation = glm::vec3(randRotation(generator), randRotation(generator), randRotation(generator));
		transform.scale = glm::vec3(scale, scale, scale);
		gCoordinator.AddComponent(entity, transform);
	
		Renderable renderable;
		renderable.color = glm::vec3(randColor(generator), randColor(generator), randColor(generator));
		gCoordinator.AddComponent(entity, renderable);
	}



	float dt = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		auto startTime = std::chrono::high_resolution_clock::now();

		//physicsSystem->Update(dt);
		
		renderSystem->Update(dt);

		Window::Update(window);

		auto stopTime = std::chrono::high_resolution_clock::now();

		dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
	}

	// Destroy framework
	Window::Destroy();
}