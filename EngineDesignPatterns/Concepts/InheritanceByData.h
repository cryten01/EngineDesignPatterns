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


class CompMap
{
public:
	void ClearEntry(int id)
	{
		storageMap.erase(id);
		std::cout << "Cleared Entry" << std::endl;
	}

	std::shared_ptr<Comp> GetEntry(int id)
	{
		std::cout << "Get Entry" << std::endl;
		return storageMap.find(id)->second;
	}

	void AddEntry(int id, std::shared_ptr<Comp> value)
	{
		storageMap.emplace(id, value);
		std::cout << "Added Entry" << std::endl;
	}

	std::map<int, std::shared_ptr<Comp>> storageMap;
};


/**
 * Note that T is here to store the IData type as key and to cast the IData into the specific type.
 */
class MapRegister
{
public:

	template <typename T>
	void CreateMap()
	{
		auto type = typeid(T).name();
		interfaceMap.emplace(type, std::make_shared<CompMap>());
		std::cout << "Created map with abstract Element" << std::endl;
	}

	template <typename T>
	void AddEntry(int id, std::shared_ptr<Comp> value)
	{
		auto type = typeid(T).name();
		auto interface = interfaceMap.find(type)->second;
		interface->AddEntry(id, value);
	}

	template <typename T>
	std::shared_ptr<T> GetEntry(int id)
	{
		auto type = typeid(T).name();
		auto interface = interfaceMap.find(type)->second;
		std::shared_ptr<Comp> entry = interface->GetEntry(id);
		return std::static_pointer_cast<T>(entry);
	}

	void ClearAllEntries(int id)
	{
		for (auto interface : interfaceMap)
		{
			interface.second->ClearEntry(id);
		}
	}

	std::map<std::string, std::shared_ptr<CompMap>> interfaceMap;
};



void InheritanceByElement()
{
	MapRegister reg;
	reg.CreateMap<int>();
	reg.CreateMap<AComp>();
	reg.CreateMap<BComp>();

	AComp data1;
	data1.value = 1234;
	Comp* aCompRef = &data1;

	AComp data2 = *static_cast<AComp*>(aCompRef);

	std::cout << data2.value << std::endl;

	// Note that only inherited IData types are possible!
	//std::shared_ptr<AComp> aIData = std::make_shared<AComp>();
	//aIData->value = 10;
	//std::shared_ptr<BComp> bIData = std::make_shared<BComp>();
	//bIData->value = 12;
	//reg.AddEntry<AComp>(0, aIData);
	//reg.AddEntry<BComp>(0, bIData);

	//aIData = reg.GetEntry<AComp>(0);
	//std::cout << aIData->value << std::endl;
	//bIData = reg.GetEntry<BComp>(0);
	//std::cout << bIData->value << std::endl;

	//reg.ClearAllEntries(0);
}