#pragma once

#include <iostream>
#include <functional>

// Aliases can be used for a specific function with the determined signature
using AliasVoidFunc = std::function<void()>;

using AliasParamFunc = std::function<int(int)>;


int ParamFunc(int number) 
{
	std::cout << "Param function called" << std::endl;
	return number;
}

void VoidFunc() 
{
	std::cout << "Void function called" << std::endl;
}

void RunVoidFuncPtrTest() 
{
	// Statically define function type (alias version)
	AliasVoidFunc function = &VoidFunc;
	function();

	// Statically define function type (typedef version)
	typedef void(*TFunction)();
	TFunction voidFunc = &VoidFunc;
	voidFunc();

	// Statically define function type (c-style version)
	void(*CFunction)();
	CFunction = &VoidFunc;
	CFunction();

	// Dynamically define function type (auto version)
	auto AFunction = &VoidFunc;
	AFunction();
}

void RunParamFuncPtrTest() 
{
	// Statically define function type (alias version)
	AliasParamFunc function = &ParamFunc;
	int w = function(10);

	// Statically define function type (typedef version)
	typedef int(*TFunction)(int);
	TFunction paramFunc = &ParamFunc;
	int x = paramFunc(10);

	// Statically define function type (c-style version)
	int(*CFunction)(int);
	CFunction = &ParamFunc;
	int y = CFunction(10);

	// Dynamically define function type (auto version)
	auto AFunction = &ParamFunc;
	int z = AFunction(10);
}