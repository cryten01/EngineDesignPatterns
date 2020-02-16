#pragma once
#include <vector>
#include <functional>

// Behavior changes in different classes 
// Behavior is always the same
// Subscribe:	Depots can subscribe in order to get notified when a key is returned.
// Publish:		Key owners can return their key. This notifies all depots (Event listeners)
// Function callback

template <typename T>
using CallbackFnPtr = bool(*)(T);


template <typename T>
struct Connections 
{
	std::vector<CallbackFnPtr<T>> callbacks;
};


template <typename T>
void Publish(Connections<T>& connections, T value)
{
	for (auto callback : connections.callbacks) 
	{
		std::cout << "Publish called" << std::endl;
		callback(value);
	}
}

template <typename T>
void Subscribe(Connections<T>& connections, CallbackFnPtr<T> callback)
{
	std::cout << "Registered function" << std::endl;
	connections.callbacks.push_back(callback);
}

template <typename T>
void Unsubscribe(Connections<T>& connections, CallbackFnPtr<T> callback)
{
	for (size_t i = 0; i < connections.callbacks.size(); i++)
	{
		if (connections.callbacks.at(i) == callback) 
		{
			std::cout << "Unregistered function" << std::endl;
			connections.callbacks.erase(connections.callbacks.begin() + i);
		}
	}
}