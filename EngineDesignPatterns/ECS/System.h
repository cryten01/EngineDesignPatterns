#pragma once

#include <vector>
#include <memory>


struct Component
{
    size_t type; // Needed for casting
};


struct Entity 
{
    std::vector<Component*> dataList;
};


class System
{
public:
    template <typename T>
    static void AddData(T& data, std::vector<Component*>& dataList)
    {
		data.type = typeid(T).hash_code();
        dataList.push_back(&data);
    }


    template <typename T>
    static T& GetData(std::vector<Component*>& dataList)
    {
        for (auto data : dataList)
        {
            if (data->type == typeid(T).hash_code()) 
            {
                return *static_cast<T*>(data);
            }
        }
    }


    template <typename T>
    static std::vector<T> GetAllData(std::vector<Component*>& dataList) 
    {
        std::vector<T> list;

		for (auto data : dataList)
		{
			if (data->type == typeid(T).hash_code())
			{
                list.push_back(*static_cast<T*>(data));
			}
		}

        return list;
    }


    template <typename T>
    static bool HasData(std::vector<Component*>& dataList)
    {
        for (auto data : dataList) 
        {
            if (data->type == typeid(T).hash_code())
            {
                return true;
            }
        }

        return false;
    }
};