#pragma once

#include <iostream>

#include "Data.h"

bool OnFoo(EntityEvent data)
{
	std::cout << "OnFoo received entity event" << std::endl;
	return true;
}