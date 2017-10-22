#include "WorldCreator.h"

#include "Street.h"
#include "Object.h"
#include "World.h"
#include "Food.h"
#include "Player.h"
#include "Exit.h"

Room* CreateMainStreet();
Room* CreateAllyWayStreet();



World* WorldCreator::CreateGameWorld()
{
	World* world = new World("earth", "where all the humans live");
	Room* mainStreet = CreateMainStreet();
	Player * player = new Player("Player", "Lonely person", mainStreet);

	Room* allyWayStreet = CreateAllyWayStreet();

	Exit* mainStreetNorthExit = new Exit("Northen way", "The way north", Exit::Direction::North, mainStreet, allyWayStreet);
	Exit* allyWaySouthExit = new Exit("Southern way", "The way south", Exit::Direction::South, allyWayStreet, mainStreet);

	mainStreetNorthExit->AttachToParent(mainStreet);
	allyWaySouthExit->AttachToParent(allyWayStreet);

	world->AttachChild(mainStreet);
	world->AttachChild(allyWayStreet);

	return world;
}

Room* CreateMainStreet() {
	Street * street = new Street("Main Street","Where everybody walks and you live");
	Object * tire = new Object("tire", "A tire left by someone on the side of the street");
	street->AttachChild(tire);
	return street;
}

Room* CreateAllyWayStreet() {
	Street * street = new Street("Ally way", "A small allyway where I can stay to relax. There is usually nobody around here");
	Food * can = new Food("can", "A can of food in preserve",5);
	Object * backpack = new Object("backpack", "My old backpack. Very useful for storing air");
	street->AttachChild(can);
	street->AttachChild(backpack);
	return street;
}
