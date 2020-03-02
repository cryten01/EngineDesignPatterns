#pragma once

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class ObjectA 
{
public: 
	void Method1()
	{
		std::cout << "Method 1" << std::endl;
	}

	void Method2()
	{
		std::cout << "Method 2" << std::endl;
	}

	void Method3()
	{
		std::cout << "Method 3" << std::endl;
	}

	void Method4()
	{
		std::cout << "Method 4" << std::endl;
	}

	void OnUpdate(float dt) 
	{
		floatValue = 1.0f;
		vec3Value = glm::vec3(1.0f);
	};

private:
	float floatValue;
	glm::vec3 vec3Value;
	int extraValue1;
	int extraValue2;
	int extraValue3;
};


class ObjectB
{
public:
	void Method1()
	{
		std::cout << "Method 1" << std::endl;
	}

	void Method2()
	{
		std::cout << "Method 2" << std::endl;
	}

	void Method3()
	{
		std::cout << "Method 3" << std::endl;
	}

	void Method4()
	{
		std::cout << "Method 4" << std::endl;
	}

	void OnUpdate(float dt)
	{
		floatValue = 1.0f;
		vec3Value = glm::vec3(1.0f);

		a.OnUpdate(dt);
	};

private:
	float floatValue;
	glm::vec3 vec3Value;
	int extraValue1;
	int extraValue2;
	int extraValue3;

	ObjectA a;
};


class ObjectC
{
public:
	void Method1()
	{
		std::cout << "Method 1" << std::endl;
	}

	void Method2()
	{
		std::cout << "Method 2" << std::endl;
	}

	void Method3()
	{
		std::cout << "Method 3" << std::endl;
	}

	void Method4()
	{
		std::cout << "Method 4" << std::endl;
	}

	void OnUpdate(float dt)
	{
		floatValue = 1.0f;
		vec3Value = glm::vec3(1.0f);

		b.OnUpdate(dt);
	};

private:
	float floatValue;
	glm::vec3 vec3Value;
	int extraValue1;
	int extraValue2;
	int extraValue3;

	ObjectB b;
};


class ObjectD
{
public:
	void Method1()
	{
		std::cout << "Method 1" << std::endl;
	}

	void Method2()
	{
		std::cout << "Method 2" << std::endl;
	}

	void Method3()
	{
		std::cout << "Method 3" << std::endl;
	}

	void Method4()
	{
		std::cout << "Method 4" << std::endl;
	}

	void OnUpdate(float dt)
	{
		floatValue = 1.0f;
		vec3Value = glm::vec3(1.0f);

		c.OnUpdate(dt);
	};

private:
	float floatValue;
	glm::vec3 vec3Value;
	int extraValue1;
	int extraValue2;
	int extraValue3;

	ObjectC c;
};

class ObjectE
{
public:
	void Method1()
	{
		std::cout << "Method 1" << std::endl;
	}

	void Method2()
	{
		std::cout << "Method 2" << std::endl;
	}

	void Method3()
	{
		std::cout << "Method 3" << std::endl;
	}

	void Method4()
	{
		std::cout << "Method 4" << std::endl;
	}

	void OnUpdate(float dt)
	{
		floatValue = 1.0f;
		vec3Value = glm::vec3(1.0f);

		d.OnUpdate(dt);
	};

private:
	float floatValue;
	glm::vec3 vec3Value;
	int extraValue1;
	int extraValue2;
	int extraValue3;

	ObjectD d;
};

class ObjectF
{
public:
	void Method1()
	{
		std::cout << "Method 1" << std::endl;
	}

	void Method2()
	{
		std::cout << "Method 2" << std::endl;
	}

	void Method3()
	{
		std::cout << "Method 3" << std::endl;
	}

	void Method4()
	{
		std::cout << "Method 4" << std::endl;
	}

	void OnUpdate(float dt)
	{
		floatValue = 1.0f;
		vec3Value = glm::vec3(1.0f);

		e.OnUpdate(dt);
	};

private:
	float floatValue;
	glm::vec3 vec3Value;
	int extraValue1;
	int extraValue2;
	int extraValue3;

	ObjectE e;
};