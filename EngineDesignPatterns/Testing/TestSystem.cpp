#include "TestSystem.h"

#include "ComponentTypes.h"
#include "../ECS/Coordinator.h"


extern Coordinator coordinator;


void TestSystem::Init()
{
}

void TestSystem::Update(float dt)
{
	for (auto const& entity : mEntities)
	{
		auto& mesh = coordinator.GetComponent<MeshComponent>(entity);
		auto& speed = coordinator.GetComponent<SpeedComponent>(entity);

		std::cout << "Mesh: " << mesh.x << " " << mesh.y << " " << mesh.z << " " << std::endl;
		std::cout << "Speed: " << speed.speed << std::endl;
	}
}