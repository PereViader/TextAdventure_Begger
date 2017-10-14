#pragma once

#include "Entity.h"

#include <string>

class Room;

class Exit :
	public Entity
{

public:

	enum class Direction {
		Error,
		North,
		South,
		East,
		West
	};

	Exit(Direction exitDirection, Room* source, Room * destination);

	Direction GetExitDirection() const;
	Room* GetExitDestination() const;
	Room* GetExitSource() const;

	static Direction ParseDirectionString(const string&);
private:
	Direction exitDirection;
	Room * source;
	Room * destination;
};

