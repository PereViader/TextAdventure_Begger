#pragma once

#include "Globals.h"

#include "Entity.h"

#include <vector>


using namespace std;

class World :
	public Entity
{
public:
	World(const string& name, const string& description);
};
