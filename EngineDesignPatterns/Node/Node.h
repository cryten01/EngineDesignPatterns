#pragma once

#include <vector>

// Why?
// Event driven (callbacks)
// Messaging

// Avoid type checks


// Data
struct NData 
{
};


// Container for holding data
struct NDataContainer 
{
	size_t id;
	std::vector<std::unique_ptr<NData>> data;
};


// Container for holding functionality systems
class Node
{
public:

};



