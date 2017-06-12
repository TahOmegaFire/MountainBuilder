#include "Headers/TTFTextW.h"
#include "Headers/Map.h"
#include <dirent.h>
//Constants for windows - TESTING AAAA
const int WINDOW_HEIGHT = 480;
const int WINDOW_WIDTH = 640;

//Function prototypes
bool Init();
bool Finish();
std::vector<Entity> LoadEntities();

SDL_Window* mainWindow = NULL;
SDL_Renderer* mainRenderer = NULL;
TextTexture curEnt;
//TextTexture curTileType;

int main(int argc, char* argv[])
{
	if(!Init())
    {
        //logger.WriteToLog("Close program");
        return -1;
    }
	
	USI width, length;
	std::cout << "Enter width: ";
	std::cin >> width;
	std::cout << "\nEnter length: ";
	std::cin >> length;
	
	Map curMap(width, length);
	if(!curEnt.LoadTTF("Res/Fonts/a.ttf", 16))
		std::cout << "\nAyye\n";
	
	std::vector<Entity> entities = LoadEntities();
	
	SDL_Color white = {255, 255, 255};
	std::string firstEnt = UtilFn::SearchAttributeValue("tpe", entities[0].m_Attributes);
	curEnt.LoadTextTexture(firstEnt, white);
	
	SDL_Event e;
	bool endProgram, pressedW, pressedS, constWorkMap = false;

    Point2D camera, mouse, Tile;
    camera.x = 0;
    camera.y = 0;
    const Uint8* currentKeyStates;
	mouse.x = mouse.y = 0;
	std::string mapName = "testmap.mp";
	
    while(!endProgram)
    {
        //Update phase
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
            case SDL_QUIT:
                endProgram = true;
                break;
			
			case SDL_MOUSEBUTTONDOWN:
				if(curMap.m_Tiles[Tile.x][Tile.y].tileType == "floor0")
					curMap.m_Tiles[Tile.x][Tile.y].tileType = "floor1";
				else
					curMap.m_Tiles[Tile.x][Tile.y].tileType = "floor0";
            }
        }
		
		SDL_GetMouseState(&mouse.x, &mouse.y);

        currentKeyStates = SDL_GetKeyboardState(NULL);
        if(currentKeyStates[SDL_SCANCODE_ESCAPE])
            endProgram = true;
		if(currentKeyStates[SDL_SCANCODE_UP])
			camera.y -= 4;
		else if(currentKeyStates[SDL_SCANCODE_DOWN])
			camera.y += 4;
		if(currentKeyStates[SDL_SCANCODE_RIGHT])
			camera.x += 4;
		else if(currentKeyStates[SDL_SCANCODE_LEFT])
			camera.x -= 4;
		if(currentKeyStates[SDL_SCANCODE_W])
		{
			if(!pressedW)
			{
				curMap.m_Tiles[Tile.x][Tile.y].m_Entity.LoadEntity(entities[0].filePath.c_str());
				std::cout << "\nPut " <<  UtilFn::SearchAttributeValue("tpe", entities[0].m_Attributes) << " entity on " << Tile.x << ", " << Tile.y << "\n";
				pressedW = true;
			}
		}
		else
			pressedW = false;
		if(currentKeyStates[SDL_SCANCODE_S] || currentKeyStates[SDL_SCANCODE_L])
		{
			if(!pressedS)
			{
				if(currentKeyStates[SDL_SCANCODE_S])
				{
					if(!constWorkMap)
					{
						std::string nMapName;
						std::cout << "Input map name. Append ! for working with this map for the whole session: ";
						std::cin >> nMapName;
						std::cout << std::endl;
						if(nMapName.front() == '!')
						{
							constWorkMap = true;
							nMapName.erase(0, 1);
							std::cout << nMapName << std::endl;
						}
						mapName = nMapName;
					}
				curMap.ExportToMapFile(mapName);
				pressedS = true;
				}
				else  //SDL_SCANCODE_L
				{
					std::string nMapName;
					std::cout << "Input map name. Append ! for working with this map for the whole session: ";
					std::cin >> nMapName;
					if(nMapName.front() == '!')
					{
						constWorkMap = true;
						nMapName.erase(0, 1);
					}
					else
						constWorkMap = false;
					mapName = nMapName;
					curMap.LoadMap(mapName);
					pressedS = true;
				}
			}
		}
		else
			pressedS = false;
		if(currentKeyStates[SDL_SCANCODE_1])
		{
			for(size_t i = 0; i < curMap.m_Width; i++)
			{
				for(size_t j = 0; j < curMap.m_Length; j++)
				{
					curMap.m_Tiles[0][j].tileType = "floor1";
					curMap.m_Tiles[i][0].tileType = "floor1";
					curMap.m_Tiles[curMap.m_Width - 1][j].tileType = "floor1";
					curMap.m_Tiles[i][curMap.m_Length - 1].tileType = "floor1";
				}
			}
		}
		
		if(camera.x < 0)
			camera.x = 0;
		else if(camera.x > curMap.m_Length * 64 - WINDOW_WIDTH)
			camera.x = curMap.m_Length * 64 - WINDOW_WIDTH;
		if(camera.y < 0)
			camera.y = 0;
		else if(camera.y > curMap.m_Length * 64 - WINDOW_HEIGHT)
			camera.y = curMap.m_Length * 64 - WINDOW_HEIGHT;
		
		Tile.x = (mouse.x + camera.x) / 64;
		Tile.y = (mouse.y + camera.y) / 64;
		SDL_Rect cTile; cTile.x = Tile.x * 64 - camera.x; cTile.y = Tile.y * 64 - camera.y; cTile.w = cTile.h = 64;
		
		
		//Render phase
        SDL_RenderClear(mainRenderer);
		
		curMap.Render(camera);
		SDL_SetRenderDrawColor(mainRenderer, 0xFF, 0xFF, 0xFF, 0xFF); 
		SDL_RenderDrawRect(mainRenderer, &cTile);
		SDL_SetRenderDrawColor(mainRenderer, 0x00, 0x00, 0x00, 0xFF); 
		
		curEnt.Render(300, 50);
		
        SDL_RenderPresent(mainRenderer);
    }
	
	Finish();
	
	return 0;
}

bool Init()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        //logger.WriteToLog("FATAL: Cannot init SDL_Init with flags SDL_INIT_VIDEO");
        return false;
    }

    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        //logger.WriteToLog("WARNING: Cannot activate linear filtering");
		std::cout << "\nWARNING: Cannot activate linear filtering\n";
    }

    mainWindow = SDL_CreateWindow("Mountain Builder v0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if(mainWindow == NULL)
    {
        //logger.WriteToLog("FATAL: Cannot create window");
        return false;
    }

    mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(mainRenderer == NULL)
    {
        //logger.WriteToLog("FATAL: Cannot create renderer");
        return false;
    }

    SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 0xFF);

    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        //logger.WriteToLog("FATAL: Cannot initialize SDL_image");
        return false;
    }
	
	if(TTF_Init() == -1)
	{
		std::cout << "Ayylmao";
		return false;
	}

    //logger.WriteToLog("Initialization complete");

    //srand(time(NULL));

    return true;
}

std::vector<Entity> LoadEntities()
{
	DIR* dir;
	dirent* pdir;
	std::vector<std::string> files;
	
	dir = opendir("Res/Data/Ent/");
	while( (pdir = readdir(dir)) )
	{
		std::string aa = pdir->d_name;
		if(aa.compare("..") != 0 && aa.compare(".") != 0)
		{
			std::string path = "Res/Data/Ent/";
			path += aa;
			files.push_back(path);
		}
	}
	
	std::vector<Entity> out;
	
	for(size_t i = 0; i < files.size(); i++)
	{
		Entity nEnt;
		nEnt.LoadEntity(files[i].c_str());
		out.push_back(nEnt);
	}
	
	return out;
}

bool Finish()
{
    SDL_DestroyWindow(mainWindow);
	
	//curTileType.FreeTexture();
	
	TTF_CloseFont(curEnt.m_Font);
	curEnt.m_Font = NULL;
	curEnt.FreeTexture();
	
	TTF_Quit();
	IMG_Quit();
    SDL_Quit();

    return true;
}
