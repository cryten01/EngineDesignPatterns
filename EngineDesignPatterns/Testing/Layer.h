#pragma once

class Layer 
{
public:
	virtual void Init() = 0;
	virtual void OnEvent() = 0;
};