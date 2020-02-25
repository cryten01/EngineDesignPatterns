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
	}

	T& GetEntry(int id) 
	{
		return storageMap.find(id)->second;
	}

	void AddEntry(int id, T value)
	{
		storageMap.emplace(id, value);
	}

private:
	std::map<int, T> storageMap;
};




class MapSystemManager
{
public:

	template <typename T> // Entry needs to be specific because of T
	void CreateInterface()
	{
		auto type = typeid(T).name();
		IMapSystemsMap.emplace(type, std::make_shared<MapSystem<T>>());

		std::cout << "Created interface with Implementation" << std::endl;
	}

	template <typename T>
	void AddEntry(int id, T value)
	{
		auto mapSystem = GetMapSystem<T>(id);
		mapSystem->AddEntry(id, value);

		std::cout << "Added Entry" << std::endl;
	}

	template <typename T>
	T& GetEntry(int id)
	{
		std::cout << "Got Entry from interface" << std::endl;

		auto mapSystem = GetMapSystem<T>(id);
		return mapSystem->GetEntry(id);
	}

	void ClearAllEntries(int id)
	{
		for (auto mapSystem : IMapSystemsMap) 
		{
			mapSystem.second->ClearEntry(id);

			std::cout << "Cleared Entry" << std::endl;
		}
	}

	template <typename T>
	std::shared_ptr<MapSystem<T>> GetMapSystem(int id)
	{
		auto type = typeid(T).name();
		auto interface = IMapSystemsMap.find(type)->second;
		return std::static_pointer_cast<MapSystem<T>>(interface);
	};

private:
	std::map<std::string, std::shared_ptr<IMapSystem>> IMapSystemsMap;
};

void InheritanceByInterface()
{
	MapSystemManager manager;
	manager.CreateInterface<int>();
	manager.CreateInterface<float>();

	manager.AddEntry<int>(0, 10);
	manager.AddEntry<float>(0, 0.5f);

	int IResult = manager.GetEntry<int>(0);
	float fResult = manager.GetEntry<float>(0);

	std::cout << fResult << std::endl;

	manager.ClearAllEntries(0);
}

