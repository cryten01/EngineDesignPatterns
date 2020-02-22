#pragma once
#include <vector>
#include <functional>

/**
 * Stations allow systems to communicate with each other without knowing the recipient.
 * This is being realized with routing an event through a station<T>.
 */

template <typename T>
using Callback = std::function<bool(T)>; // Use lambdas because those are type independent

template <typename T>
struct StationData
{
	std::vector<Callback<T>> subscriber;
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
		for (auto callback : station<T>.subscriber)
		{
			std::cout << "Publish called" << std::endl;
			callback(event);
		}
	}

	template <typename T>
	void Subscribe(Callback<T> callback)
	{
		std::cout << "Registered function" << std::endl;
		station<T>.subscriber.push_back(callback); 
	}

	template <typename T>
	void Unsubscribe(Callback<T>& callback)
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