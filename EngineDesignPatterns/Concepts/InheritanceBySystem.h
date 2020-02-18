#pragma once

#include <vector>
#include <iostream>
#include <map>


/**
 * INHERITANCE BY SYSTEM
 *
 * For this version virtual inheritance is used per system (see Interface).
 * 
 * Note that T methods cannot be abstracted and that the storage must be coupled with the system implementation.
 */


class IMapSystem
{
public:
	virtual ~IMapSystem() = default;
	virtual void ClearEntry(int id) = 0; // Note the essential difference here
};

template <typename T>
class MapSystem : public IMapSystem
{
public:
	virtual void ClearEntry(int id) override
	{
		storageMap.erase(id);
		std::cout << "Cleared Entry" << std::endl;
	}

	void AddEntry(int id, T value)
	{
		storageMap.emplace(id, value);
		std::cout << "Added Entry" << std::endl;
	}

private:
	std::map<int, T> storageMap;
};


struct MapSystemManager
{
	template <typename T> // Entry needs to be specific because of T
	void CreateInterface()
	{
		auto type = typeid(T).name();
		interfaceMap.emplace(type, std::make_shared<MapSystem<T>>());
		std::cout << "Created interface with Implementation" << std::endl;
	}

	template <typename T>
	void AddEntry(int id, T value)
	{
		auto type = typeid(T).name();
		auto interface = interfaceMap.find(type)->second;
		auto implementation = std::static_pointer_cast<MapSystem<T>>(interface);
		implementation->AddEntry(id, value);
	}

	void ClearAllEntries(int id)
	{
		for (auto interface : interfaceMap)
		{
			interface.second->ClearEntry(id);
		}
	}

	std::map<std::string, std::shared_ptr<IMapSystem>> interfaceMap;
};

void InheritanceByInterface()
{
	MapSystemManager manager;
	manager.CreateInterface<int>();
	manager.CreateInterface<float>();

	manager.AddEntry<int>(0, 10);
	manager.AddEntry<float>(0, 0.5f);

	manager.ClearAllEntries(0);
}

