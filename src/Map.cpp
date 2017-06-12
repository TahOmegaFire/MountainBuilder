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
			nTile.tileType = "floor0";
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
	std::vector<UtilFn::Attribute> tiles;
	std::vector<UtilFn::Attribute> entities;

	if(f_Map.good())
	{
		//CleanMap();
		bool startMap = false;
		USI jay = 0;
		while(getline(f_Map, s_Map))
		{
//			std::cout << s_Map << std::endl;
			if(!startMap)
			{
				char name = s_Map.front();
				switch(name)
				{
				case '#': //Width
					m_Width = stoi(s_Map.substr(3));
					std::cout << "Width = " << m_Width << std::endl;
					break;

				case '$': //Length
					m_Length = stoi(s_Map.substr(3));
					std::cout << "Length = " << m_Length << std::endl;
					break;

				case 't':
				{
					UtilFn::Attribute nAtt = UtilFn::ParseMapAttribute(s_Map.substr(1));
					tiles.push_back(nAtt);
					std::cout << nAtt.name << " = " << nAtt.value << std::endl;
					break;
				}
				case 'e':
				{
					UtilFn::Attribute nAtt = UtilFn::ParseMapAttribute(s_Map.substr(1));
					entities.push_back(nAtt);
					std::cout << nAtt.name << " = " << nAtt.value << std::endl;
					break;
				}

				case '[':
					if(strcmp(s_Map.c_str(), "[MAP]") == 0)
					{
						startMap = true; //Yee
						CleanMap();
					}

				default:
					break;
				}
				
			}
			else
			{
				//Read map struct data
				for(USI i = 0; i < s_Map.length(); i++)
				{
					bool put = false;
					for(USI j = 0; j < tiles.size(); j++)
					{
						if(s_Map[i] == tiles[j].name[0])
						{
							m_Tiles[i][jay].tileType = tiles[j].value;
							put = true;
							break;
						}
					}

					if(!put)
					{
						for(USI j = 0; j < entities.size(); j++)
						{
							if(s_Map[i] == entities[j].name[0])
							{
								m_Tiles[i][jay].tileType = "floor0";
								std::string path = "Res/Data/Ent/";
								path.append(entities[j].value);
								path.append(".ent");
								m_Tiles[i][jay].m_Entity.LoadEntity(path.c_str());
								put = true;
								break;
							}
						}
					}

					if(!put)
						std::cout << "Sad reacts only\n";
				}
				jay++;
			}
		}
	}
	else
		std::cout << "Bad filename" << std::endl;
	
	f_Map.close();
}

void Map::Render(Point2D camera_pos)
{
	for(USI i = 0; i < m_Width; i++)
   	{
        for(USI j = 0; j < m_Length; j++)
        {
        	if(m_Tiles[i][j].tileType == "floor1")
			{
        		floor1.Render(TILESIZE * i - camera_pos.x, TILESIZE * j - camera_pos.y);
			}
        }
   	}
}

void Map::ExportToMapFile(std::string name_of_map)
{
	//Get names to put on map of entities and tiles
	std::vector<UtilFn::Attribute> tileNames;
	std::vector<UtilFn::Attribute> entNames;
	for(USI i = 0; i < m_Width; i++)
	{
		for(USI j = 0; j < m_Length; j++)
		{
			bool is = false;
			for(USI nI = 0; nI < tileNames.size(); nI++)
			{
				if(m_Tiles[i][j].tileType == tileNames[nI].value)
				{
					is = true;
					break;
				}
			}

			if(!is)
			{
				UtilFn::Attribute nAt;
				nAt.name = m_Tiles[i][j].tileType.back();
				nAt.value = m_Tiles[i][j].tileType;
                std::cout << nAt.name << " " << nAt.value << "\n";
				tileNames.push_back(nAt);
			}
			std::string entityType = UtilFn::SearchAttributeValue("tpe", m_Tiles[i][j].m_Entity.m_Attributes);

			if(entityType != "-1")
			{
				UtilFn::Attribute nAt;
				nAt.name = entityType.front(); 				
				nAt.value = entityType;
				entNames.push_back(nAt);
			}
		}
	}
	//Load header of map
	std::ofstream nMap;
	nMap.open(name_of_map);
	nMap << "# = " << m_Width << std::endl << "$ = " << m_Length << std::endl; 
	for(USI i = 0; i < tileNames.size(); i++)
	{
		nMap << 't' << tileNames[i].name << " = " << tileNames[i].value << std::endl;
	}
	for(USI i = 0; i < entNames.size(); i++)
	{
		nMap << 'e' << entNames[i].name << " = " << entNames[i].value << std::endl;
	}

	nMap << "[MAP]" << std::endl;
	
	for(USI j = 0; j < m_Width; j++)
	{
		for(USI i = 0; i < m_Length; i++)
		{
			if(m_Tiles[i][j].m_Entity.filePath != "")
				nMap << UtilFn::SearchAttributeValue("tpe", m_Tiles[i][j].m_Entity.m_Attributes).front();
			else
				nMap << m_Tiles[i][j].tileType.back();	
		}

		nMap << std::endl;
	}

	nMap.close();
}
