#pragma once

#include "DCS.h"

class DataSystem : System
{
public:
	template <typename T>
	void AddData(T& data, std::vector<Data*>& dataList)
	{
		data.type = typeid(T).hash_code();
		dataList.push_back(&data);
	}


	template <typename T>
	T& GetData(std::vector<Data*>& dataList)
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
	std::vector<T> GetAllData(std::vector<Data*>& dataList)
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
	bool HasData(std::vector<Data*>& dataList)
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