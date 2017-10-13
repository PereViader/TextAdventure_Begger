#pragma once

class World;
class Room;

class WorldCreator
{
public:
	static World* CreateGameWorld();

private:

	static Room* CreateMainStreet();
};

