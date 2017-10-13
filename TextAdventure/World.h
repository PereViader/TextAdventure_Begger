#pragma once

#include "Globals.h"

#include "Entity.h"

#include <vector>


using namespace std;

class World
{
public:
	World();
	virtual ~World();

	Frame_Return Update();

public:
	vector<Entity*> gameEntities;
};
