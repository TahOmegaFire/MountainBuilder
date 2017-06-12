#ifndef TILE_H
#define TILE_H

#include "Entity.h"

struct Tile
{
	enum Type {EMPTY, TILE1} m_Type;
	std::string tileType; //To be implemented
	Entity m_Entity;
	int x, y;
	//TODO: Fill in the other characteristics of a tile (e.g. grappable, et cetera)
};

#endif // TILE_H
