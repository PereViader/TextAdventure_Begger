#include "WorldCreator.h"

#include "Street.h"
#include "Object.h"
#include "World.h"
#include "Food.h"
#include "Player.h"
#include "Exit.h"
#include "Shop.h"
#include "ItemContainer.h"

Room* CreateMainStreet();
Room* CreateAllyWayStreet();
Room* CreateHiddenShop();



World* WorldCreator::CreateGameWorld()
{
	World* world = new World("earth", "where all the humans live");
	Room* mainStreet = CreateMainStreet();
	Player * player = new Player("Player", "Lonely person", mainStreet);

	Room* allyWayStreet = CreateAllyWayStreet();
	Room* hiddenShop = CreateHiddenShop();

	Exit* mainStreetNorthExit = new Exit("Northen way", "The way north", Exit::Direction::North, mainStreet, allyWayStreet);
	Exit* allyWaySouthExit = new Exit("Southern way", "The way south", Exit::Direction::South, allyWayStreet, mainStreet);
	
	Exit* allyWayEastExit = new Exit("Eastern way", "There's something this way", Exit::Direction::East, allyWayStreet, hiddenShop);
	Exit* hiddenShopWestExit = new Exit("Western exit", "The way back to the street", Exit::Direction::West, hiddenShop, allyWayStreet);

	mainStreetNorthExit->AttachToParent(mainStreet);
	allyWaySouthExit->AttachToParent(allyWayStreet);

	allyWayEastExit->AttachToParent(allyWayStreet);
	hiddenShopWestExit->AttachToParent(hiddenShop);


	world->AttachChild(mainStreet);
	world->AttachChild(allyWayStreet);
	world->AttachChild(hiddenShop);

	return world;
}

Room* CreateMainStreet() {
	Street * street = new Street("Main Street","Where everybody walks and you live",0.25f);
	Object * tire = new Object("tire", "A tire left by someone on the side of the street");
	street->AttachChild(tire);
	return street;
}

Room* CreateAllyWayStreet() {
	Street * street = new Street("Ally way", "A small allyway where I can stay to relax. There is usually nobody around here", 0.0f);
	ItemContainer * backpack = new ItemContainer("backpack", "My old backpack. Very useful for storing air");
	Food * can = new Food("can", "A can of food in preserve", 5);
	Object * rubbish = new Object("rubbish", "Some random stuff");
	backpack->AddItem(rubbish);
	backpack->AddItem(can);
	street->AttachChild(backpack);
	return street;
}

Room* CreateHiddenShop() {
	Shop* shop = new Shop("HiddenShop", "A place for us tu buy");
	Item* smallCan = new Food("small can", "Something to eat of unknown procedence", 5);
	shop->AddItem(smallCan, 3);
	return shop;
}
