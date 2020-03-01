#pragma once

#include <iostream>

struct Abstract
{};


template <typename T>
struct Specific : Abstract
{
	T val;
};


void Casting() 
{
	// Raw pointer version (no guarantee that value is alive!)
	Specific<int> data;
	data.val = 1234;
	Abstract* aPtr = &data;
	Specific<int>* sPtr = static_cast<Specific<int>*>(aPtr);

	std::cout << sPtr->val << std::endl;


	// Smart pointer version
	std::shared_ptr<Specific<int>> smartData = std::make_shared<Specific<int>>();
	smartData->val = 2345;

	std::shared_ptr<Abstract> smartAPtr = smartData;
	std::shared_ptr<Specific<int>> smartSPtr = std::static_pointer_cast<Specific<int>>(smartAPtr);

	std::cout << smartSPtr->val << std::endl;


	// Reference version (do not use!)
	Specific<int> data2;
	data.val = 3456;

	Abstract& aRef = data2;
	Specific<int>& sRef = static_cast<Specific<int>&>(aRef);

	std::cout << sRef.val << std::endl;
}