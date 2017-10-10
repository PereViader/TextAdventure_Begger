#include "Room.h"

#include <iostream>

#include "Entity.h"
using namespace std;

Room::Room()
{
}


Room::~Room()
{
}

void Room::Look() const
{
	cout << this->name << endl;
	cout << this->description << endl;
	for (vector<Entity*>::const_iterator it = childEntities.cbegin(); it != childEntities.cend(); it++) {
		(*it)->Look();
	}
}

Room::Type Room::GetRoomType() const
{
	return roomType;
}

vector<Exit*> Room::GetExits() const
{
	vector<Entity*> exitsEntity = FindAll(Entity::Type::exit);
	vector<Exit*> exits(exitsEntity.size());
	for (vector<Entity*>::const_iterator it = exitsEntity.cbegin(); it != exitsEntity.cend(); ++it) {
		exits.push_back((Exit*)*it);
	}
	return exits;
}
