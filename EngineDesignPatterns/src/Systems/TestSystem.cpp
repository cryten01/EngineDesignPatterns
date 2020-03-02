#include "TestSystem.h"

#include "ECS/Coordinator.h"
#include "Components/AFComponents.h"

extern Coordinator gCoordinator;

void TestSystem::Init()
{

}

void TestSystem::Update(float dt)
{
	auto componentAStorage = gCoordinator.GetComponentStorage<ComponentA>();
	auto componentBStorage = gCoordinator.GetComponentStorage<ComponentB>();
	auto componentCStorage = gCoordinator.GetComponentStorage<ComponentC>();
	auto componentDStorage = gCoordinator.GetComponentStorage<ComponentD>();
	auto componentEStorage = gCoordinator.GetComponentStorage<ComponentE>();
	auto componentFStorage = gCoordinator.GetComponentStorage<ComponentF>();

	for (auto entity : m_Entities)
	{
		ComponentA& a = componentAStorage->GetEntry(entity);
		ComponentB& b = componentBStorage->GetEntry(entity);
		ComponentC& c = componentCStorage->GetEntry(entity);
		ComponentD& d = componentDStorage->GetEntry(entity);
		ComponentE& e = componentEStorage->GetEntry(entity);
		ComponentF& f = componentFStorage->GetEntry(entity);

		a.floatValue = 1.0f;
		a.vec3Value = glm::vec3(1.0f);

		b.floatValue = 1.0f;
		b.vec3Value = glm::vec3(1.0f);

		c.floatValue = 1.0f;
		c.vec3Value = glm::vec3(1.0f);

		d.floatValue = 1.0f;
		d.vec3Value = glm::vec3(1.0f);

		e.floatValue = 1.0f;
		e.vec3Value = glm::vec3(1.0f);

		f.floatValue = 1.0f;
		f.vec3Value = glm::vec3(1.0f);
	}
}
