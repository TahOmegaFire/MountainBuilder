#include "Headers/Map.h"

Map::Map(USI w, USI l)
{
	m_Width = w;
	m_Length = l;
	
	floor1.LoadTexture("Res/Img/Tiles/ye.png", false);
	
	CleanMap();
}

Map::~Map()
{
	
}

void Map::CleanMap()
{
	m_Tiles.clear();
	for(USI i = 0; i < m_Width; i++)
	{
		std::vector<Tile> nVector;
		
		for(USI j = 0; j < m_Length; j++)
		{
			Tile nTile;
			nTile.m_Type = Tile::EMPTY;
			nTile.x = i;
			nTile.y = j;
			nVector.push_back(nTile);
		}
		
		m_Tiles.push_back(nVector);
	}
}

void Map::LoadMap(std::string map_dir)
{
	std::ifstream f_Map;
	f_Map.open(map_dir.c_str(), std::ifstream::in);
	std::string s_Map;
	USI len = 0;
	USI wid = 0;
	
	while(getline(f_Map, s_Map))
	{
		std::cout << s_Map << std::endl;
		++len;
		if(s_Map.size() > wid)
		{
			if(wid != 0)
				std::cout << "Warning: Variable size in map file" << std::endl;
			wid = s_Map.size();
		}
	}
	
	m_Length = len;
	m_Width = wid;
	UtilFn::Print2Values(m_Width, m_Length);
	//check what values are m_Len and m_Wid
	
	CleanMap();
	
	f_Map.clear();
	f_Map.seekg(0, f_Map.beg);
	
	len = 0;
	wid = 0;

	char c;
	while(f_Map >> std::noskipws >> c)
	{
		if(c == 'F')
			m_Tiles[wid][len].m_Type = Tile::EMPTY;
		else if(c == 'S')
		{
			m_Tiles[wid][len].m_Type = Tile::EMPTY;
			//spawnPoint.x = TILESIZE * wid;
			//spawnPoint.y = TILESIZE * len;
		}
		else
			m_Tiles[wid][len].m_Type = Tile::TILE1;

		wid++;
		if(wid == m_Width)
		{       //Maybe change to m_Width - 1?
			len++;
			wid = 0;
		}
	}
	
	f_Map.close();
	
	//PrepareMap();
}

void Map::Render(Point2D camera_pos)
{
	for(USI i = 0; i < m_Width; i++)
    {
        for(USI j = 0; j < m_Length; j++)
        {
            if(m_Tiles[i][j].m_Type == Tile::TILE1)
			{
                floor1.Render(TILESIZE * i - camera_pos.x, TILESIZE * j - camera_pos.y);
			}
        }
    }
}

void ExportToMapFile(std::string name_of_map)
{
	std::vector<UtilFn::Attribute> entNames;
	std::vector<UtilFn::Attribute> tileNames;
	for(USI i = 0; i < m_Width; i++)
    {
        for(USI j = 0; j < m_Length; j++)
        {
			bool is = false;
			for(USI nI = 0; nI < tileNames.size(); nI++)
			{
				if(m_Tiles[i][j].tileType == tileNames[nI].value)
					is = true;
			}
			
			if(!is)
			{
				UtilFn::Attribute nAt;
				if(m_Tiles[i][j].tileType == "Empty")
					nAt.name = 	"0";
				else
					nAt.name = m_Tiles[i][j].tileType.substr(5);
				nAt.value = m_Tiles[i][j].tileType;
				tileNames.push_back(nAt);
			}
			
			if(m_Tiles[i][j].m_Entity.filePath != "")
			{
				UtilFn::Attribute nAt; //TODO: Continue fam
			}
        }
    }
}