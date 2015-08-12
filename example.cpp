//#define EX_BIND_DIAGNOSTIC_STATIC_ASSERT
//#define EX_BIND_DIAGNOSTIC_ENABLE_IF
#include "ex_bind.hpp"

#include <iostream>
#include <functional>
#include <unordered_map>
#include <string>

int foo_1p(int a)
{
	return a;
}

int foo_2p(int a, int b)
{
	return a + b;
}

int foo_3p(int a, int b, int c)
{
	return a + b + c;
}

int foo_4p(int a, int b, int c, int d)
{
	return a + b + c + d;
}

int foo_5p(int a, int b, int c, int d, int e)
{
	return a + b + c + d + e;
}

int foo_6p(int a, int b, int c, int d, int e, int f)
{
	return a + b + c + d + e + f;
}

int foo_7p(int a, int b, int c, int d, int e, int f, std::string g)
{
	return a + b + c + d + e + f + std::stoi(g);
}

int main()
{
	std::unordered_map<std::string, std::function<int(int, int, int, int, int, int, std::string)>> map;

	using ex::ph;

	map["foo_1p"] = ex::bind(foo_1p, ph, ph, ph, ph, ph, ph);
	map["foo_2p"] = ex::bind(foo_2p, ph, ph, ph, ph, ph);
	map["foo_3p"] = ex::bind(foo_3p, ph, ph, ph, ph);
	map["foo_4p"] = ex::bind(foo_4p, ph, ph, ph);
	map["foo_5p"] = ex::bind(foo_5p, ph, ph);
	map["foo_6p"] = ex::bind(foo_6p, ph);
	map["foo_7p"] = foo_7p;

	for (const auto& f : map)
	{
		std::cout << f.first << " = " << f.second(1, 1, 1, 1, 1, 1, "101") << std::endl;
	}

	/*
		Output should be:
			foo_1p = 1
			foo_2p = 2
			foo_3p = 3
			foo_4p = 4
			foo_5p = 5
			foo_6p = 6
			foo_7p = 107
	*/
}
