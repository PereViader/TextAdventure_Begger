#pragma once

#include "Player.h"
#include "Entity.h"

#include <vector>

class World
{
public:
	World();
	virtual ~World();

	vector<Entity*> gameEntities;
	Player * player;
};

