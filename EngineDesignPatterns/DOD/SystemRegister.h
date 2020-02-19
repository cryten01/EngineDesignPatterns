#pragma once

#include <map>
#include <iostream>

#include "System.h"


// aka System Manager
namespace SystemRegister
{
	// anonymous namespace makes access private
	namespace 
	{
		static std::map<size_t, std::shared_ptr<System>> systemsMap;
	}

	template<typename T>
	void Add()
	{
		size_t type = typeid(T).hash_code();
		std::shared_ptr<System> entry = std::make_shared<T>();
		systemsMap.emplace(type, entry);
	}

	template<typename T>
	std::shared_ptr<T> Get()
	{
		size_t type = typeid(T).hash_code();
		auto entry = systemsMap.find(type)->second;
		return std::static_pointer_cast<T>(entry);
	}

	template<typename T>
	void Remove()
	{
		size_t type = typeid(T).hash_code();
		systemsMap.erase(type);
	}
};


