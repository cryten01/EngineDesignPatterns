#pragma once

#include <cstdint>
#include <bitset>

// A simple type alias
using EntityID = std::uint32_t;

// Used to define the size of arrays later on (determined by factory)
const EntityID MAX_ENTITIES = 20000;

// A simple type alias
using ComponentID = std::uint8_t;

// Used to define the maximum amount of component types an entity can hold (determined by factory)
const ComponentID MAX_COMPONENTS = 32;

// A simple type alias
using Signature = std::bitset<MAX_COMPONENTS>;