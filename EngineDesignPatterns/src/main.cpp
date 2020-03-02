
#include <random>
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "ECS/Coordinator.h"

#include "Event/Station.h"
#include "Event/EventTypes.h"

#include "Core/Window.h"

#include "Graphics/Shader.h"
#include "Graphics/GPULog.h"

#include "Systems/RenderSystem.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/TestSystem.h"

#include "Components/Gravity.h"
#include "Components/Rigidbody.h"
#include "Components/Camera.h"
#include "Components/Transform.h"
#include "Components/Renderable.h"
#include "Components/AFComponents.h"

#include "Classic/CameraObj.h"
#include "Classic/GeometryObj.h"

#include "Params.h"


//---------------------------
// Globals
//---------------------------

Coordinator gCoordinator; 

int FPS = 0;
int frameCount = 0;
float lastFrameTime = float(glfwGetTime());

int startupFPS; // records when FIRST_CAPTURETIME is reached
int runtimeFPS; // records when SECOND_CAPTURETIME is reached



void WriteFPSIntoFile(std::string filePath)
{
	std::ofstream out(filePath, std::ios_base::app);

	out << "#StartFPS: "  << startupFPS << "\t#RuntimeFPS: " << runtimeFPS << std::endl;
	out.close();
}


void CountFPS() 
{
	float currentTime = glfwGetTime();

	frameCount++;
	if (currentTime - lastFrameTime >= 1.0) {
		FPS = frameCount;
		frameCount = 0;
		lastFrameTime += 1.0;
	}

	if (lastFrameTime >= SECOND_FPS_CAPTURE_TIME)
	{
		runtimeFPS = FPS;
	}
	else if (lastFrameTime >= FIRST_FPS_CAPTURE_TIME)
	{
		startupFPS = FPS;
	}

	std::cout << "FPS: " << FPS << std::endl; // for debugging only
}


void RunECSVersion()
{
	GLFWwindow* window = Window::Create("EngineDesignPatterns", 1024, 768);

	GPULog::Init();

	gCoordinator.Init();

	gCoordinator.RegisterComponent<Gravity>();
	gCoordinator.RegisterComponent<RigidBody>();
	gCoordinator.RegisterComponent<Renderable>();
	gCoordinator.RegisterComponent<Transform>();
	gCoordinator.RegisterComponent<Camera>();

	gCoordinator.RegisterComponent<ComponentA>();
	gCoordinator.RegisterComponent<ComponentB>();
	gCoordinator.RegisterComponent<ComponentC>();
	gCoordinator.RegisterComponent<ComponentD>();
	gCoordinator.RegisterComponent<ComponentE>();
	gCoordinator.RegisterComponent<ComponentF>();

	auto testSystem = gCoordinator.RegisterSystem<TestSystem>();
	{
		Signature signature;
		signature.set(gCoordinator.GetComponentType<ComponentA>());
		signature.set(gCoordinator.GetComponentType<ComponentB>());
		signature.set(gCoordinator.GetComponentType<ComponentC>());
		signature.set(gCoordinator.GetComponentType<ComponentD>());
		signature.set(gCoordinator.GetComponentType<ComponentE>());
		signature.set(gCoordinator.GetComponentType<ComponentF>());
		gCoordinator.SetSystemSignature<TestSystem>(signature);
	}

	testSystem->Init();

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


	std::vector<EntityID> entities(MAX_ENTITIES - 1);

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



		ComponentA a;
		a.floatValue = randGravity(generator);
		a.vec3Value = glm::vec3(randRotation(generator), randRotation(generator), randRotation(generator));

		ComponentB b;
		b.floatValue = randGravity(generator);
		b.vec3Value = glm::vec3(randRotation(generator), randRotation(generator), randRotation(generator));

		ComponentC c;
		c.floatValue = randGravity(generator);
		c.vec3Value = glm::vec3(randRotation(generator), randRotation(generator), randRotation(generator));

		ComponentD d;
		d.floatValue = randGravity(generator);
		d.vec3Value = glm::vec3(randRotation(generator), randRotation(generator), randRotation(generator));

		ComponentE e;
		e.floatValue = randGravity(generator);
		e.vec3Value = glm::vec3(randRotation(generator), randRotation(generator), randRotation(generator));

		ComponentF f;
		f.floatValue = randGravity(generator);
		f.vec3Value = glm::vec3(randRotation(generator), randRotation(generator), randRotation(generator));
	}


	float dt = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		auto startTime = std::chrono::high_resolution_clock::now();

		CountFPS();

		physicsSystem->Update(dt);

		renderSystem->Update(dt);

		testSystem->Update(dt);

		Window::Update(window);

		auto stopTime = std::chrono::high_resolution_clock::now();

		dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
	}

	Window::Destroy();
}


void RunClassicVersion()
{
	GLFWwindow* window = Window::Create("EngineDesignPatterns", 1024, 768);

	GPULog::Init();

	// Set GL defaults here
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Create default shader
	std::shared_ptr<Shader> shader = std::make_unique<Shader>("assets/shaders/flatColor.vert", "assets/shaders/flatColor.frag");

	// Create camera
	ViewFrustumDimensions dimensions;
	dimensions.aspect = (float)(1024 / 768);
	dimensions.fov = 45.0f;
	dimensions.nearPlane = 0.1f;
	dimensions.farPlane = 1000.0f;

	CameraObj camera(dimensions, shader);

	std::default_random_engine generator;
	std::uniform_real_distribution<float> randPosition(-100.0f, 100.0f);
	std::uniform_real_distribution<float> randRotation(0.0f, 3.0f);
	std::uniform_real_distribution<float> randScale(3.0f, 5.0f);
	std::uniform_real_distribution<float> randColor(0.0f, 1.0f);
	std::uniform_real_distribution<float> randGravity(-10.0f, -1.0f);

	float scale = randScale(generator);

	std::vector<std::shared_ptr<GeometryObj>> cubes;

	for (size_t i = 0; i < MAX_ENTITIES - 1; i++)
	{
		PhysicsObj physics;
		physics.force = glm::vec3(0.0f, randGravity(generator), 0.0f);
		physics.velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		physics.acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

		TransformObj transform;
		transform.position = glm::vec3(randPosition(generator), randPosition(generator), randPosition(generator));
		transform.rotation = glm::vec3(randRotation(generator), randRotation(generator), randRotation(generator));
		transform.scale = glm::vec3(scale, scale, scale);

		glm::vec3 color = glm::vec3(randColor(generator), randColor(generator), randColor(generator));

		GeometryData geometry = GeometryObj::createCubeGeometry(1, 1, 1);

		cubes.push_back(std::make_shared<GeometryObj>(geometry, physics, color, transform, shader));
	}



	float dt = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		auto startTime = std::chrono::high_resolution_clock::now();
		float currentTime = glfwGetTime();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		CountFPS();

		shader->Use();

		camera.OnUpdate(dt);

		for (auto c : cubes) 
		{
			c->OnUpdate(dt);
		}

		Window::Update(window);

		auto stopTime = std::chrono::high_resolution_clock::now();

		dt = std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
	}

	Window::Destroy();
}



int main()
{
	if (ECS_MODE) 
	{
		RunECSVersion();
		WriteFPSIntoFile("assets/profiling/ecs.fps");
	}
	else
	{
		RunClassicVersion();
		WriteFPSIntoFile("assets/profiling/classic.fps");
	}
}