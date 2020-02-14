#pragma once

#include <iostream>
#include "DataSet.h"
#include "DCFC.h"

// Avoid type checks
// No inheritance only composition
// Every struct must be unique
// Function and data are treated as same
// Overriding the same function possible only with inheritance


struct TransformFS : Set
{
	void OnReceive(Container dc)
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


struct MessagingFS : Set
{
	void Send(std::vector<MessagingFS> m, Container dc)
	{
		for (auto i : m)
			i.OnReceive(dc);
	}

	// Must be redefined in every class?
	void OnReceive(Container dc)
	{
		std::cout << "Message received" << std::endl;
	};
};


struct SetFS : Set
{
	/**
	 * A factory for creating different types of data sets.
	 * Set hash and type name so that each unit can be casted safely.
	 */
	template<typename T>
	T CreateSet()
	{
		T set;
		set.tHash = typeid(T).hash_code();
		set.tName = typeid(T).name();
		return set;
	}


	void AttachSet(Container& container, Set& set)
	{
		container.sets.push_back(&set);
		std::cout << "Attached set" << std::endl;
	}


	template<typename T>
	void GetSet(Container& container, T& set)
	{
		for (auto ds : container.sets)
		{
			if (ds->tHash == typeid(T).hash_code())
			{
				set = *static_cast<T*>(ds);
			}
		}
	}

	template<typename T>
	void RemoveSet(Container& container)
	{
		for (size_t i = 0; i < container.sets.size(); i++)
		{
			if (container.sets.at(i)->tHash == typeid(T).hash_code())
			{
				container.sets.erase(container.sets.begin() + i);
			}
		}
	}

	template<typename T>
	bool HasSet(Container& container)
	{
		for (auto ds : container.sets)
		{
			if (ds->tHash == typeid(T).hash_code())
			{
				return true;
			}
		}

		return false;
	}
};


struct FSContainer : Container
{
	SetFS sets;
	MessagingFS messaging;
};







