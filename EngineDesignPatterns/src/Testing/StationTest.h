#pragma once

#include <iostream>
#include <functional>

#include "ECS/Coordinator.h"
#include "Event/Station.h"
#include "Testing/ComponentTypes.h"
#include "Event/EventTypes.h"


struct AType
{
	int m_Value = 20;

	bool OnEntityEvent(EntityDestroyedEvent e) 
	{
		std::cout << "AType member function OnEntityEvent(EntityEvent e) bound with std::bind received event " << m_Value * 2 << std::endl;
		return true;
	}

	// A function wrapper
	void InitCallbacks()
	{
		// Capture [this] for accessing class instance variables
		auto lambda = [this](EntityDestroyedEvent data) -> bool
		{
			// Possibility of calling member functions
			this->OnEntityEvent(data);

			// Possibility of calling member variables
			std::cout << "AType lambda() received entity event with value: " << m_Value << std::endl;
			
			return true;
		};

		// Use lambdas when not using outside variables (faster and more modern!)
		StationSystem::Subscribe<EntityDestroyedEvent>(lambda);

		// Use std::bind when using function needs to be called outside as well
		StationSystem::Subscribe<EntityDestroyedEvent>(std::bind(&AType::OnEntityEvent, this, std::placeholders::_1));
	}
};

struct BType
{
	std::string m_String = "Hello";

	bool OnEntityEvent(EntityDestroyedEvent e)
	{
		std::cout << "BType member function bound with std::bind received event " << std::endl;
		return true;
	}

	void InitCallbacks()
	{
		auto lambda = [this](CollisionEvent data) -> bool
		{
			std::cout << "BType lambda() received event with value: " << data.isColliding << std::endl;
			return true;
		};
		StationSystem::Subscribe<CollisionEvent>(lambda);

		StationSystem::Subscribe<EntityDestroyedEvent>(std::bind(&BType::OnEntityEvent, this, std::placeholders::_1));
	}
};





