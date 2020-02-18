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


/**
 * Stations allow systems to communicate with each other without knowing the exact recipient.
 * This is being realized with routing everything through a station.
 */


template <typename T>
struct Station
{
	std::vector<CallbackFnPtr<T>> subscriber;
};


namespace StationSystem
{
	template <typename T>
	void Publish(Station<T>& station, T event)
	{
		for (auto callback : station.subscriber)
		{
			std::cout << "Publish called" << std::endl;
			callback(event);
		}
	}

	template <typename T>
	void Subscribe(Station<T>& station, CallbackFnPtr<T> callback)
	{
		std::cout << "Registered function" << std::endl;
		station.subscriber.push_back(callback);
	}

	template <typename T>
	void Unsubscribe(Station<T>& station, CallbackFnPtr<T> callback)
	{
		for (size_t i = 0; i < station.subscriber.size(); i++)
		{
			if (station.subscriber.at(i) == callback)
			{
				std::cout << "Unregistered function" << std::endl;
				station.subscriber.erase(station.subscriber.begin() + i);
			}
		}
	}
};