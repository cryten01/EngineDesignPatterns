#pragma once
#include <vector>
#include <functional>

// Behavior changes in different classes 
// Behavior is always the same
// Subscribe:	Depots can subscribe in order to get notified when a entity is returned.
// Publish:		entity owners can return their entity. This notifies all depots (Event listeners)
// Function callback


/**
 * Stations allow systems to communicate with each other without knowing the recipient.
 * This is being realized with routing an event through a station<T>.
 */

template <typename T>
using CallbackFnPtr = std::function<bool(T)>; // Use lambdas because those are type independent

template <typename T>
struct StationData
{
	std::vector<CallbackFnPtr<T>> subscriber;
};

namespace StationSystem
{
	namespace 
	{
		// The compiler creates one station for each data type when using templates in combination with static
		template <typename T>
		static StationData<T> station; 
	}

	template <typename T>
	void Publish(T event)
	{
		// Publish event to station members
		for (auto callback : station<T>.subscriber)
		{
			std::cout << "Publish called" << std::endl;
			callback(event);
		}
	}

	template <typename T>
	void Subscribe(CallbackFnPtr<T> callback)
	{
		std::cout << "Registered function" << std::endl;

		// <T> is necessary in order to target correct station
		station<T>.subscriber.push_back(callback); 
	}

	template <typename T>
	void Unsubscribe(CallbackFnPtr<T> callback)
	{
		for (size_t i = 0; i < station<T>.subscriber.size(); i++)
		{
			if (station<T>.subscriber.at(i) == callback)
			{
				std::cout << "Unregistered function" << std::endl;
				station<T>.subscriber.erase(station<T>.subscriber.begin() + i);
			}
		}
	}
};