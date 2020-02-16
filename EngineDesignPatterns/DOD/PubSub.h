#pragma once
#include <vector>

// Behavior changes in different classes 
// Behavior is always the same
// Subscribe:	Depots can subscribe in order to get notified when a key is returned.
// Publish:		Key owners can return their key. This notifies all depots (Event listeners)
// Function callback

struct Node
{
};

struct Connections 
{
	std::vector<Node*> conn;
};


template <typename T>
void Publish(Connections& connections, T value)
{
	// Send to all connections
}

void Subscribe(Connections& connections, Node* node)
{
	connections.conn.push_back(node);
}

void Unsubscribe(Connections& connections, Node* node)
{
	for (size_t i = 0; i < connections.conn.size(); i++)
	{
		if (connections.conn.at(i) == node)
			connections.conn.erase(connections.conn.begin() + i);
	}
}