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

	Exit* mainStreetNorthExit = new Exit(Exit::Direction::North, mainStreet, allyWayStreet);
	Exit* allyWaySouthExit = new Exit(Exit::Direction::South, allyWayStreet, mainStreet);

	mainStreetNorthExit->AttackToParent(mainStreet);
	allyWaySouthExit->AttackToParent(allyWayStreet);

	world->AttachChild(player);
	world->AttachChild(mainStreet);
	world->AttachChild(allyWayStreet);

	return world;
}

Room* CreateMainStreet() {
	Street * street = new Street("Main Street","Where everybody walks and you live");
	Object * tire = new Object("Tire", "A tire left by someone on the side of the street");
	street->AttachChild(tire);
	return street;
}

Room* CreateAllyWayStreet() {
	Street * street = new Street("Ally way", "A small allyway where I can stay to relax. There is usually nobody around here");
	Food * can = new Food("Can", "A can of food in preserve",5);
	street->AttachChild(can);
	return street;
}
