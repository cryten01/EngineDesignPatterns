#pragma once

#include <iostream>
#include "DataSet.h"

// Avoid type checks
// No inheritance only composition
// Every struct must be unique
// Function and data are treated as same


// Overriding the same function possible only with inheritance

struct FunctionSet 
{
	size_t id;
	size_t tHash;
	const char* tName;
};


struct TransformFS : FunctionSet
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


struct MessagingFS : FunctionSet
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


struct SetFS : FunctionSet
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

	template<typename C, typename T>
	void AttachSet(C& container, T& set)
	{
		container.sets.push_back(&set);
		std::cout << "Attached set" << std::endl;
	}

	template<typename C, typename T>
	void GetSet(C& container, T& set) 
	{
		for (auto ds : container.sets)
		{
			if (ds->tHash == typeid(T).hash_code())
			{
				set = *static_cast<T*>(ds);
			}
		}
	}

	template <typename C, typename T>
	void RemoveSet(C& container)
	{
		for (size_t i = 0; i < container.sets.size(); i++)
		{
			if (container.sets.at(i)->tHash == typeid(T).hash_code())
			{
				container.sets.erase(container.sets.begin() + i);
			}
		}
	}

	template <typename C, typename T>
	bool HasSet(C& container)
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


struct FSContainer
{
	std::vector<FunctionSet*> sets;

	//TransformFS transform;
	SetFS set;
	MessagingFS messaging;
};






