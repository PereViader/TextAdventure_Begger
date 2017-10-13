#pragma once

#include "Entity.h"

#include <string>

class Room;

class Exit :
	public Entity
{

public:

	enum ExitDirection {
		Error,
		North,
		South,
		East,
		West
	};

	Exit(ExitDirection exitDirection, Room* source, Room * destination);

	ExitDirection GetExitDirection() const;
	Room* GetExitDestination() const;
	Room* GetExitSource() const;

	static ExitDirection ParseDirectionString(const string&);
private:
	ExitDirection exitDirection;
	Room * source;
	Room * destination;
};

