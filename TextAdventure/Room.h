#pragma once

#include "Entity.h"

#include <vector>

using namespace std;

class Exit;

class Room :
	public Entity
{
public:
	enum class Type {
		Error,
		Shop,
		Street
	};

	const Room::Type GetRoomType() const;
	const vector<Exit*> GetExits() const;

protected:
	Room(string name, string description, Room::Type roomType);

private:
	const Room::Type roomType;
};

