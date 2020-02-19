#pragma once

#include <iostream>
#include <functional>

#include "Data.h"
#include "System.h"
#include "Station.h"


struct AType
{
	int m_Value = 20;

	bool OnEntityEvent(EntityEvent e) 
	{
		std::cout << "AType member function received entity event " << m_Value * 2 << std::endl;
		return true;
	}

	void Subscribe()
	{
		// Capture [this] for accessing class instance variables
		auto lambda = [this](EntityEvent data) -> bool
		{
			std::cout << "AType received entity event with value: " << m_Value << std::endl;
			return true;
		};

		// Use lambdas when not using outside variables (faster and more modern!)
		StationSystem::Subscribe<EntityEvent>(lambda);

		// Use std::bind when using instance variables
		StationSystem::Subscribe<EntityEvent>(std::bind(&AType::OnEntityEvent, this, std::placeholders::_1));
	}
};

struct BType
{
	std::string m_String = "Hello";

	bool OnEntityEvent(EntityEvent e)
	{
		std::cout << "BType member function received entity event " << std::endl;
		return true;
	}

	void Subscribe()
	{
		auto lambda = [this](EntityEvent data) -> bool
		{
			std::cout << "BType received entity event with value: " << m_String << std::endl;
			return true;
		};

		StationSystem::Subscribe<EntityEvent>(lambda);
		StationSystem::Subscribe<EntityEvent>(std::bind(&BType::OnEntityEvent, this, std::placeholders::_1));
	}
};





