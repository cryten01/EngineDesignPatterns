#pragma once

#include <vector>
#include <memory>

// WHY?
// Separate Data and Function
// Multi-core processing
// Save multi-threading


struct Data
{
    size_t type; // Needed for casting
};


// Collection of data
struct DataContainer
{
	std::vector<Data*> dataList;
};



struct System 
{
};


// Collection of systems
struct SystemsContainer 
{
    std::vector<System*> systemList;
};