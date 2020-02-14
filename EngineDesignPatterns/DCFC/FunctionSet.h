#pragma once

#include <iostream>
#include "DataSet.h"

// Avoid type checks
// No inheritance only composition
// Every struct must be unique
// Function and data are treated as same


// Overriding the same function possible only with inheritance


struct TransformFS
{
	void OnReceive(DSContainer dc)
	{
		// Check signature (cast test?)
	}

	void ModifyPosition(glm::vec3 position)
	{
		std::cout << "This function modifies a position" << std::endl;
	}

	void ModifyVelocity(float velocity)
	{
		std::cout << "This function modifies the velocity" << std::endl;
	}

	void ModifyScale(glm::vec3 scale)
	{
		std::cout << "This function modifies the scale" << std::endl;
	}
};


struct MessagingFS
{
	void Send(std::vector<MessagingFS> m, DSContainer dc)
	{
		for (auto i : m)
			i.OnReceive(dc);
	}

	// Must be redefined in every class?
	void OnReceive(DSContainer dc)
	{
		std::cout << "Message received" << std::endl;
	};
};


struct ContainerFS 
{
	/**
	 * A factory for creating different types of data sets.
	 * Set hash and type name so that each unit can be casted safely.
	 */
	template<typename T>
	T CreateDataSetOfType() 
	{
		T set;
		set.hash = typeid(T).hash_code();
		set.name = typeid(T).name();
		return set;
	}

	template<typename T>
	void AttachDataSet(DSContainer& container, T& set) 
	{
		container.dataSets.push_back(&set);
	}

	template<typename T>
	void GetDataSetOfType(DSContainer& container, T& set) 
	{
		for (auto ds : container.dataSets)
		{
			if (ds->hash == typeid(T).hash_code())
			{
				std::cout << "Found object" << std::endl;
				set = *static_cast<T*>(ds);
			}
		}
	}
};


struct FSContainer
{
	bool active = true;
	TransformFS transform;
	ContainerFS container;
	MessagingFS messaging;
};






