#include "Room.h"

#include <iostream>

#include "Entity.h"
#include "Exit.h"

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

	const vector<Entity*> itemsInTheRoom = FindAll(Entity::Type::Item);
	if (itemsInTheRoom.size() == 0) {
		cout << "There is nothing you can take around here" << endl;
	}
	else {
		cout << "Stuff you can see around:" << endl;
		for (vector<Entity*>::const_iterator it = itemsInTheRoom.cbegin(); it != itemsInTheRoom.cend(); ++it) {
			Entity* currentEntity = *it;
			cout << currentEntity->GetName() << endl;
		}
	}

	const vector<Exit*> exitsOfTheRoom = GetExits();
	if (exitsOfTheRoom.size() == 0) {
		cout << "There is no way out of this place" << endl;
	}
	else {
		cout << "Exits of the room:" << endl;
		for (vector<Exit*>::const_iterator it = exitsOfTheRoom.cbegin(); it != exitsOfTheRoom.cend(); ++it) {
			const Exit* currentExit = *it;
			cout << currentExit->GetName() << ": " << currentExit->GetDescription() << " - " << currentExit->GetExitDirectionString() << endl;
		}
	}
}
