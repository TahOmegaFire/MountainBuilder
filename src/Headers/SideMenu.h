#ifndef SMENU_H
#define SMENU_H

#include "Entity.h"

class SideMenu
{
public:
	SideMenu();
	~SideMenu();
	
	std::vector<Entity> availableEntities;
	int funcState;
	
	void Render();
	void Update(Point2D);
	//TODO: Mostly everything hah

};

#endif //SMENU_H