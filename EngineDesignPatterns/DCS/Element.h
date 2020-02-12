#pragma once

#include "DCS.h"

/**
 *	typename S = Specific type
 *	typename A = Abstract type
 */

class ElementSystem : System
{
public:
	template <typename S, typename A>
	void AddElement(S& element, std::vector<A*>& elementList)
	{
		element.type = typeid(S).hash_code();
		elementList.push_back(&element);
	}


	template <typename S, typename A>
	S& GetElement(std::vector<A*>& elementList)
	{
		for (auto element : elementList)
		{
			if (element->type == typeid(S).hash_code())
			{
				return *static_cast<S*>(element);
			}
		}
	}


	template <typename S, typename A>
	std::vector<S> GetAllElements(std::vector<A*>& elementList)
	{
		std::vector<S> list;

		for (auto element : elementList)
		{
			if (element->type == typeid(S).hash_code())
			{
				list.push_back(*static_cast<S*>(element));
			}
		}

		return list;
	}


	template <typename S, typename A>
	bool HasElement(std::vector<A*>& elementList)
	{
		for (auto element : elementList)
		{
			if (element->type == typeid(S).hash_code())
			{
				return true;
			}
		}

		return false;
	}
};