#pragma once

#include <iostream>
#include "DataSet.h"

// Avoid type checks
// No inheritance only composition
// Every struct must be unique
// Function and data are treated as same


// Overriding the same function possible only with inheritance


struct Transform
{
	void OnReceive(DataContainer dc)
	{
		// Check signature (cast test?)
		ModifyPosition(dc.p, dc.i);
		ModifyVelocity(dc.v);
	}

	void ModifyPosition(Position p, Input i)
	{
		std::cout << "This function modifies a position" << std::endl;
	}

	void ModifyVelocity(Velocity v)
	{
		std::cout << "This function modifies the velocity" << std::endl;
	}
};


struct Messaging
{
	void Send(Messaging m, DataContainer dc)
	{
		m.OnReceive(dc);
	}

	// Must be redefined in every class
	void OnReceive(DataContainer dc)
	{
		std::cout << "Message received" << std::endl;
	};
};


struct FuncContainer
{
	bool active = true;
	Transform transform;
	Messaging messaging;
};






