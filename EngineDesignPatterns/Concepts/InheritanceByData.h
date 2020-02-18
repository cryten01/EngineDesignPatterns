#pragma once

#include <vector>
#include <iostream>
#include <map>

// Let abstract logic be abstract logic without needing to know a IData type

/**
 * INHERITANCE BY DATA
 *
 * For this version inheritance is used per component.
 *
 * Note that only components can be stored inside storages.
 * Decoupling between data and logic is desired in both cases.
 */


struct Comp
{};

struct AComp : Comp // Note the essential difference here
{
	float value;
};

struct BComp : Comp
{
	float value;
};

// Decoupling between data and logic
struct CompMap 
{
	std::map<int, std::shared_ptr<Comp>> storageMap;
};

struct RegMap 
{
	std::map<std::string, CompMap> interfaceMap;
};


class CompMapSystem
{
public:
	void ClearEntry(CompMap& map, int id)
	{
		map.storageMap.erase(id);
		std::cout << "Cleared Entry" << std::endl;
	}

	std::shared_ptr<Comp> GetEntry(CompMap& map, int id)
	{
		std::cout << "Get Entry" << std::endl;
		std::shared_ptr<Comp> entry = map.storageMap.find(id)->second;
		return entry;
	}

	void AddEntry(CompMap& map, int id, std::shared_ptr<Comp> value)
	{
		map.storageMap.emplace(id, value);
		std::cout << "Added Entry" << std::endl;
	}
};


/**
 * Note that T is here to store the IData type as key and to cast the IData into the specific type.
 */
class MapRegisterSystem
{
public:

	template <typename T>
	void AddMap(RegMap& map)
	{
		auto type = typeid(T).name();
		map.interfaceMap.emplace(type, CompMap());
		std::cout << "Created abstract component map" << std::endl;
	}

	template <typename T>
	void AddEntry(RegMap& map, int id, std::shared_ptr<T> value)
	{
		auto type = typeid(T).name();
		auto compMap = map.interfaceMap.find(type)->second;
		system.AddEntry(compMap, id, value);
	}

	template <typename T>
	std::shared_ptr<T> GetEntry(RegMap& map, int id)
	{
		auto type = typeid(T).name();
		auto compMap = map.interfaceMap.find(type)->second;
		auto entry = system.GetEntry(compMap, id);
		return std::static_pointer_cast<T>(entry);
	}

	void ClearAllEntries(RegMap& map, int id)
	{
		for (auto interface : map.interfaceMap)
		{
			auto compMap = interface.second;
			system.ClearEntry(compMap, id);
		}
	}

private:
	CompMapSystem system;
};



void InheritanceByData()
{
	RegMap regMap;
	MapRegisterSystem system;
	system.AddMap<int>(regMap);
	system.AddMap<AComp>(regMap);
	system.AddMap<BComp>(regMap);

	std::shared_ptr<AComp> data = std::make_shared<AComp>();
	data->value = 120;

	system.AddEntry<AComp>(regMap, 0, data);
	std::shared_ptr<AComp> result = system.GetEntry<AComp>(regMap, 0);

	std::cout << result->value << std::endl;

}