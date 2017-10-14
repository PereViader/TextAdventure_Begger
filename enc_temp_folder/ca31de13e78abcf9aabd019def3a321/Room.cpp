#include "Room.h"

#include <iostream>

#include "Entity.h"
using namespace std;

Room::Room(string name, string description, Room::Type roomType) : roomType(roomType), Entity(name, description, Entity::Type::Room)
{
}

const Room::Type Room::GetRoomType() const
{
	return roomType;
}

const vector<Exit*> Room::GetExits() const
{
	vector<Entity*> exitsEntity = FindAll(Entity::Type::Exit);
	vector<Exit*> exits;
	for (vector<Entity*>::const_iterator it = exitsEntity.cbegin(); it != exitsEntity.cend(); ++it) {
		exits.push_back((Exit*)*it);
	}
	return exits;
}

void Room::Look() const
{
	cout << this->name << endl;
	cout << this->description << endl;
	if (childEntities.size() == 0) {
		cout << "There is nothing you can take around here" << endl;
	}
	else {
		cout << "Stuff you can see around:" << endl;
		for (vector<Entity*>::const_iterator it = childEntities.cbegin(); it != childEntities.cend(); it++) {
			cout << (*it)->GetName() << endl;
		}
	}
}
