#pragma once

#include <memory>
#include <iostream>

#include "DCS.h"

// Why?
// Event driven (callbacks)
// Messaging

// Avoid type checks


struct MessageData
{
	std::vector<MessageSystem*> connections;
};


struct MessageSystem
{
	void Send(Container container, MessageData recipents) 
	{
		for (auto conn : recipents.connections)
		{
			conn->Receive(container);
		}
	};

	void Receive(Container container)
	{
	};
};