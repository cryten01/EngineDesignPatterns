#pragma once

#include "DCS.h"

/**
 *	typename S = Specific type
 *	typename A = Abstract type
 */


// Container operations

struct ContainerSystem : FunctionSet
{
public:	// Use VA_ARGS for ensuring all necessary values
	template <typename T>
	T CreateElement()
	{
		T element;
		element.type = typeid(T).hash_code();
		return element;
	}

	template <typename T>
	void AddElement(T& element, std::vector<DataSet*>& elementList)
	{
		elementList.push_back(&element);
	}


	template <typename T>
	void RemoveElement(T& element, std::vector<DataSet*>& elementList)
	{
		for (size_t i = 0; i < elementList.size(); i++)
		{
			if (element.type == elementList.at(i)->type)
				elementList.erase(elementList.begin() + i);
		}
	}


	template <typename T>
	T& GetElement(std::vector<DataSet*>& elementList)
	{
		for (auto element : elementList)
		{
			if (element->type == typeid(T).hash_code())
			{
				return *static_cast<T*>(element);
			}
		}
	}


	template <typename T>
	std::vector<T> GetAllElements(std::vector<DataSet*>& elementList)
	{
		std::vector<T> list;

		for (auto element : elementList)
		{
			if (element->type == typeid(T).hash_code())
			{
				list.push_back(*static_cast<T*>(element));
			}
		}

		return list;
	}


	template <typename T>
	bool HasElement(std::vector<DataSet*>& elementList)
	{
		for (auto element : elementList)
		{
			if (element->type == typeid(T).hash_code())
			{
				return true;
			}
		}

		return false;
	}
};