#pragma once

#include <map>
#include <iostream>

#include "System.h"



// Aka System Manager

struct SystemRegistryData
{
	std::map<size_t, std::shared_ptr<System>> registerMap;
};

class SystemRegistrySystem : public System
{
public:
	template<typename T>
	void AddSystem(SystemRegistryData& s)
	{
		size_t type = typeid(T).hash_code();
		std::shared_ptr<System> entry = std::make_shared<T>();
		s.registerMap.emplace(type, entry);
	}

	template<typename T>
	std::shared_ptr<T> GetSystem(SystemRegistryData& s)
	{
		size_t type = typeid(T).hash_code();
		auto entry = s.registerMap.find(type)->second;
		return std::static_pointer_cast<T>(entry);
	}

	template<typename T>
	void RemoveSystem(SystemRegistryData& s)
	{
		size_t type = typeid(T).hash_code();
		s.registerMap.erase(type);
	}
};


