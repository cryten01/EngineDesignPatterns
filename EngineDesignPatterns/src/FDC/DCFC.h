#pragma once

#include <vector>

struct Set 
{
	size_t id;
	size_t tHash;
	const char* tName;
};

struct Container 
{
	std::vector<Set*> sets;
};