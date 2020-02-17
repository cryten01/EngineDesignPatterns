#pragma once

#include <vector>
#include <iostream>
#include <map>

// Let abstract logic be abstract logic without needing to know a data type

/**
 * Here the inheritance is used for all Data types.
 */

struct Data
{
};

struct AData : Data // Note the essential difference here
{
	float value;
};

struct BData : Data
{
	float value;
};


class ElementMap
{
public:
	void ClearEntry(int id)
	{
		storageMap.erase(id);
		std::cout << "Cleared Entry" << std::endl;
	}

	std::shared_ptr<Data> GetEntry(int id)
	{
		std::cout << "Get Entry" << std::endl;
		return storageMap.find(id)->second;
	}

	void AddEntry(int id, std::shared_ptr<Data> value)
	{
		storageMap.emplace(id, value);
		std::cout << "Added Entry" << std::endl;
	}

	std::map<int, std::shared_ptr<Data>> storageMap;
};


/**
 * Note that T is here to store the data type as key and to cast the data into the specific type.
 */
class ElementMapRegister
{
public:

	template <typename T>
	void CreateMap()
	{
		auto type = typeid(T).name();
		interfaceMap.emplace(type, std::make_shared<ElementMap>());
		std::cout << "Created map with abstract Element" << std::endl;
	}

	template <typename T>
	void AddEntry(int id, std::shared_ptr<Data> value)
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
		std::shared_ptr<Data> entry = interface->GetEntry(id);
		return std::static_pointer_cast<T>(entry);
	}

	void ClearAllEntries(int id)
	{
		for (auto interface : interfaceMap)
		{
			interface.second->ClearEntry(id);
		}
	}

	std::map<std::string, std::shared_ptr<ElementMap>> interfaceMap;
};



void InheritanceByElement()
{
	ElementMapRegister reg;
	reg.CreateMap<int>();
	reg.CreateMap<AData>();
	reg.CreateMap<BData>();

	// Note that only inherited Data types are possible!
	std::shared_ptr<AData> aData = std::make_shared<AData>();
	aData->value = 10;
	std::shared_ptr<BData> bData = std::make_shared<BData>();
	bData->value = 12;
	reg.AddEntry<AData>(0, aData);
	reg.AddEntry<BData>(0, bData);

	aData = reg.GetEntry<AData>(0);
	std::cout << aData->value << std::endl;
	bData = reg.GetEntry<BData>(0);
	std::cout << bData->value << std::endl;

	reg.ClearAllEntries(0);

	//std::shared_ptr<MeshData> test = std::make_shared<MeshData>();
	//test->value = 10;
	
	//std::vector<std::shared_ptr<Data>> dvec;
	//dvec.push_back(test);

	//std::shared_ptr<MeshData> fromList = std::static_pointer_cast<MeshData>(dvec.at(0));
	//std::cout << fromList->value << std::endl;
}




/**
 * Here the virtual inheritance is used per interface or system.
 * Note that T methods cannot be abstracted.
 */
class Interface
{
public:
	virtual ~Interface() = default;
	virtual void ClearEntry(int id) = 0; // Note the essential difference here
};

template <typename T>
class Implementation : public Interface
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

	std::map<int, T> storageMap;
};


struct MapManager
{
	template <typename T> // Entry needs to be specific because of T
	void CreateInterface()
	{
		auto type = typeid(T).name();
		interfaceMap.emplace(type, std::make_shared<Implementation<T>>());
		std::cout << "Created interface with Implementation" << std::endl;
	}

	template <typename T>
	void AddEntry(int id, T value)
	{
		auto type = typeid(T).name();
		auto interface = interfaceMap.find(type)->second;
		auto implementation = std::static_pointer_cast<Implementation<T>>(interface);
		implementation->AddEntry(id, value);
	}

	void ClearAllEntries(int id)
	{
		for (auto interface : interfaceMap)
		{
			interface.second->ClearEntry(id);
		}
	}

	std::map<std::string, std::shared_ptr<Interface>> interfaceMap;
};

void InheritanceByInterface()
{
	MapManager manager;
	manager.CreateInterface<int>();
	manager.CreateInterface<float>();

	manager.AddEntry<int>(0, 10);
	manager.AddEntry<float>(0, 0.5f);

	manager.ClearAllEntries(0);
}

