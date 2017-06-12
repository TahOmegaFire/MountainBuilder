#include "Headers/Entity.h"

Entity::Entity()
{
    isPassable = false;
	isLoaded = false;
	entityType = "Null";
	filePath = "";
}

Entity::~Entity()
{
}

bool Entity::LoadEntity(const char* path)
{
    std::ifstream file;

    file.open(path, std::ifstream::in);

    if(file.is_open())
    {
        std::string line;
        while(getline(file, line))
        {
			UtilFn::Attribute nAt;
			nAt.name = line.substr(0, 3);
			nAt.value = line.substr(6);
			
			if(nAt.name == "img")
			{
				if(!m_Texture.LoadTexture(nAt.value.c_str(), false))
				   return false;
			}
			
			m_Attributes.push_back(nAt);
        }
        file.close();

        isLoaded = true;
		filePath = path;
        return true;
    }

    return false;
}

void Entity::AssignEntity(const Entity& other)
{
    isPassable = other.isPassable;
    isLoaded = other.isLoaded;
    m_Texture.LoadTexture(other.m_Texture.imagePath.c_str(), false);
}

