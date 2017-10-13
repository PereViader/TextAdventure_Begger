#include "World.h"


World::World()
{
}


World::~World()
{
}

Frame_Return World::Update()
{
	Frame_Return update_return = Frame_Return::Continue;
	for (vector<Entity*>::iterator it = gameEntities.begin(); update_return == Frame_Return::Continue && it != gameEntities.end(); it++) {
		(*it)->Update();
	}
	return update_return;
}
