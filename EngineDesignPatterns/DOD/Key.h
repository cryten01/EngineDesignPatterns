#pragma once
#include <queue>
#include <vector>
#include <cstdint>




// A simple type alias (helps in changing data type if necessary)
using Key = std::uint32_t;

// Used to define the size of arrays later on
const Key MAX_KEYS = 5000;


struct KeyFactory
{
	Key mKeyCreator;
	std::queue<Key> mFreeKeys;
};


void ReturnKey(KeyFactory& factory, Key key)
{
	// Notify Register that key has been returned

	// Recycle key
	factory.mFreeKeys.push(key);
}

Key IssueKey(KeyFactory& factory)
{
	if (!factory.mFreeKeys.empty())
	{
		Key key = factory.mFreeKeys.front();
		factory.mFreeKeys.pop();
		return key;
	}
	else
	{
		factory.mKeyCreator++;
		return factory.mKeyCreator;
	}
}