#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include "TexW.h"
#include "Utils.h"
#include <fstream>
#include <istream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstring>

class Map
{
public:
    Map(USI w, USI l);
    ~Map();
	
    std::vector<std::vector<Tile> > m_Tiles;
	
	void CleanMap();
	void LoadMap(std::string);
	void Render(Point2D);
	void ExportToMapFile(std::string name_of_map);
	
	USI m_Width, m_Length;
	TexW floor1;
};

#endif // MAP_H
 
