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
Room* CreateUnderground();
Room* CreateShop();



World* WorldCreator::CreateGameWorld()
{
	World* world = new World("earth", "where all the humans live");
	
	Room* mainStreet = CreateMainStreet();
	Room* allyWayStreet = CreateAllyWayStreet();
	Room* shop = CreateShop();
	Room* underground = CreateUnderground();
	world->AttachChild(mainStreet);
	world->AttachChild(allyWayStreet);
	world->AttachChild(shop);
	world->AttachChild(underground);

	Exit* mainStreetNorthExit = new Exit("Northen way", "The way north", Exit::Direction::North, mainStreet, allyWayStreet);
	Exit* allyWaySouthExit = new Exit("Southern way", "The way south", Exit::Direction::South, allyWayStreet, mainStreet);
	mainStreetNorthExit->AttachToParent(mainStreet);
	allyWaySouthExit->AttachToParent(allyWayStreet);

	Exit* mainStreetEastExit = new Exit("Eastern way", "There is a shop this way", Exit::Direction::East, mainStreet, shop);
	Exit* shopWestExit = new Exit("Western exit", "The way back to the street", Exit::Direction::West, shop, mainStreet);
	mainStreetEastExit->AttachToParent(mainStreet);
	shopWestExit->AttachToParent(shop);

	Exit* mainStreetWestExit = new Exit("Western way", "The underground entrance", Exit::Direction::West, mainStreet, underground);
	Exit* undergroundNorthExit = new Exit("Northen way", "The underground entrance", Exit::Direction::North, underground, mainStreet);
	mainStreetWestExit->AttachToParent(mainStreet);
	undergroundNorthExit->AttachToParent(underground);

	Player * player = new Player("Player", "Lonely person");
	player->AttachToParent(allyWayStreet);

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

Room * CreateUnderground()
{
	Street * underground = new Street("Underground", "It's hot and full of people", 0.3f);
	Object * oldTicket = new Object("old ticket", "An old and dusty ticket on the corner");
	Food * energyDrink = new Food("cola", "A half full cola tin", 3);
	underground->AttachChild(oldTicket);
	underground->AttachChild(energyDrink);
	return underground;
}

Room* CreateShop() {
	Shop* shop = new Shop("Shop", "A place for us tu buy");
	Item* smallCanPrototype = new Food("small can", "Something to eat of unknown procedence", 5);
	Item* betterCanPrototype = new Food("better can", "Looks nice and must taste nicer", 11);
	shop->AddAsSellableItemPropotype(smallCanPrototype, 3);
	shop->AddAsSellableItemPropotype(betterCanPrototype, 6);

	return shop;
}
