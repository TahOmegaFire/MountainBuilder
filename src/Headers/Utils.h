//Header of Utils.cpp
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>
#include <vector>

typedef unsigned short int USI;
struct Point2D {int x, y;};

const short int TILESIZE = 64;
const float GRAVITY = -0.8;

namespace UtilFn
{
	struct Attribute
	{
		std::string name;
		std::string value;
	};
	
	size_t SearchAttributeIndex(std::string nme, std::vector<Attribute> vector);
	
	std::string SearchAttributeValue(std::string nme, std::vector<Attribute> vector);

	Attribute ParseMapAttribute(std::string at);
	
	inline void Print2Values(int f, int s)
	{
		std::cout << f << " | " << s << std::endl;
	}
}
#endif //UTILS_H
