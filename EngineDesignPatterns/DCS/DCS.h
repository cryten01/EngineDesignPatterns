#pragma once

#include <vector>
#include <memory>

// WHY?
// Separate Data and Function
// Multi-core processing
// Save multi-threading


// Abstract type for all data types
struct Data
{
    size_t type; // Needed for casting
};


// Abstract type for all system types
struct System
{
	size_t type; // Needed for casting
};


// Generic container of data, systems or any other type
template <typename T>
struct Container 
{
    std::vector<T*> elements;
};


