//Header of Entity.cpp
#ifndef ENTITY_H
#define ENTITY_H

#include <fstream>
#include <vector>
#include "Utils.h"
#include "TexW.h"

class Entity
{
public:
	Entity();
	~Entity();

	//Entity operator=(const Entity& other);
	std::string entityType, filePath;
	std::vector<UtilFn::Attribute> m_Attributes;

	virtual bool LoadEntity(const char* path);
	void AssignEntity(const Entity& other);

	bool isPassable, isLoaded;
	TexW m_Texture;
};


#endif //ENTITY_H
