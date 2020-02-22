#pragma once

#include <variant>

struct A 
{};

struct B
{};

void DoVariant()
{
	// A type safe union for avoiding invalid states
	// Note that this needs cpp 2017
	std::variant<A, B> variant;

	variant = A{};
	variant = B{};
}