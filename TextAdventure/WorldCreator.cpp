#include "WorldCreator.h"

#include "Street.h"
#include "Object.h"
#include "World.h"
#include "Player.h"

World* WorldCreator::CreateGameWorld()
{
	World* world = new World("earth", "where all the humans live");
	Room* street = CreateMainStreet();
	Player * player = new Player("Player", "Lonely person", street);

	world->AttachChild(player);
	world->AttachChild(street);

	return world;
}

Room* WorldCreator::CreateMainStreet() {
	Street * street = new Street("Main Street","Where everybody walks and you live");
	Object * tire = new Object("Tire", "A tire left by someone on the side of the street");
	street->AttachChild(tire);
	return street;
}
