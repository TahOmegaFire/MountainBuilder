#include "Headers/Utils.h"

std::string UtilFn::SearchAttributeValue(std::string nme, std::vector<Attribute> vector)
{
	for(size_t i = 0; i < vector.size(); i++)
	{
		if(vector[i].name == nme)
			return vector[i].value;
	}
	
	return "-1";
}

size_t UtilFn::SearchAttributeIndex(std::string nme, std::vector<Attribute> vector)
{
	for(size_t i = 0; i < vector.size(); i++)
	{
		if(vector[i].name == nme)
			return i;
	}
	
	return -1;
}