#pragma once
#include <queue>
#include <vector>
#include <cstdint>




// A simple type alias (helps in changing data type if necessary)
using Key = std::uint32_t;

struct KeyFactory
{
	Key keyCreator;
	std::queue<Key> freeKeys;
};

class KeyFactorySystem 
{
public:
	void ReturnKey(KeyFactory& factory, Key key)
	{
		// Recycle key
		factory.freeKeys.push(key);

		// Notify Register that key has been returned
	}

	Key IssueKey(KeyFactory& factory)
	{
		if (!factory.freeKeys.empty())
		{
			Key key = factory.freeKeys.front();
			factory.freeKeys.pop();
			return key;
		}
		else
		{
			factory.keyCreator++;
			return factory.keyCreator;
		}
	}
};
