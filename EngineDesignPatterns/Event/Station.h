#pragma once
#include <vector>
#include <queue>
#include <functional>
#include <utility>

/**
 * Stations allow systems to communicate with each other without knowing the recipient.
 * This is being realized with routing an event through a station<T>.
 */


using CallbackID = std::uint32_t;

template <typename T>
using CallbackFunctionPtr = std::function<bool(T)>; // Use lambdas as value because those are type independent



template <typename T>
struct StationData
{
	// An id generator
	CallbackID nextCallbackID = 0;

	// Queue of unused entity IDs
	std::queue<CallbackID> availableIDs{};

	// A vector with pairs of callback ids and their corresponding function pointers
	std::vector<std::pair<CallbackID, CallbackFunctionPtr<T>>> subscribers;
};

namespace StationSystem
{
	namespace 
	{
		// The compiler creates one station for each data type 
		// when using templates in combination with static.
		template <typename T>
		static StationData<T> station; 
	}

	template <typename T>
	CallbackID GenerateID()
	{
		CallbackID id;

		// Use already generated ids first
		if (!station<T>.availableIDs.empty())
		{
			id = station<T>.availableIDs.front();
			station<T>.availableIDs.pop();
		}
		else 
		{
			id = station<T>.nextCallbackID;
		}

		// Increment the value so that the next callbackID registered will be different
		station<T>.nextCallbackID++;

		std::cout << "Registered function with id: " << id << std::endl;

		return id;
	}

	template <typename T>
	void DestroyID(CallbackID id) 
	{
		// Push id back into queue
		station<T>.availableIDs.push(id);
	}


	template <typename T>
	void Publish(T event)
	{
		for (auto pair : station<T>.subscribers)
		{
			std::cout << "Publish called" << std::endl;
			pair.second(event);
		}
	}

	template <typename T>
	CallbackID Subscribe(CallbackFunctionPtr<T> callback)
	{
		CallbackID id = GenerateID<T>();

		station<T>.subscribers.push_back(std::make_pair(id, callback));

		return id;
	}

	template <typename T>
	void Unsubscribe(CallbackID id)
	{
		for (size_t i = 0; i < station<T>.subscribers.size(); i++)
		{
			if (station<T>.subscribers.at(i).first == id)
			{
				DestroyID<T>(id);

				station<T>.subscribers.erase(station<T>.subscribers.begin() + i);
			}
		}

		std::cout << "Unregistered function" << std::endl;
	}
};