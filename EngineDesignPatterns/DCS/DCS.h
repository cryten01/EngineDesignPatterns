#pragma once

#include <vector>
#include <memory>
#include <bitset>

// WHY?
// Separate Data and Function
// Multi-core processing
// Save multi-threading



/**
 *  Abstract type of a single elementary unit
 */
struct Function
{
	size_t guid;
	size_t type; // Needed for casting from abstract to specific
};


struct Data
{
	size_t guid;
	size_t type; // Needed for casting from abstract to specific
};


/**
 *	Container of elements.
 *  Note that there can be only 1 unit per component type
 */
struct ContainerD
{
	size_t guid;
	std::bitset<32> dataTypes;
	std::vector<Data*> data;
};


