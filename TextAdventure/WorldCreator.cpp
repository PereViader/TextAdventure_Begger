#include "WorldCreator.h"

#include "Street.h"
#include "Object.h"
#include "World.h"
#include "Player.h"

World* WorldCreator::CreateGameWorld()
{
	World* world = new World();
	Room* street = CreateMainStreet();
	Player * player = new Player("Player", "Lonely person", street);

	world->gameEntities.push_back(player);
	world->gameEntities.push_back(street);

	return world;
}

Room* WorldCreator::CreateMainStreet() {
	Street * street = new Street("Main Street","Where everybody walks and you live");
	Object * tire = new Object("Tire", "A tire left by someone on the side of the street");
	street->Attach(tire);
	return street;
}
