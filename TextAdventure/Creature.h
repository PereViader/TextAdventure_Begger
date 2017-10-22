#pragma once

#include "Entity.h"

class Room;

class Creature :
	public Entity
{
public:
	enum class Type{
		Player
	};

	const Creature::Type GetCreatureType() const;

protected:
	Creature(string name, string description, Room* startingRoom, Creature::Type creatureType);

	Room* GetCurrentRoom() const;
	void Move(Room*);

private:
	Creature::Type creatureType;
};

