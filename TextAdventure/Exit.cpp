#include "Exit.h"



Exit::Exit(Direction exitDirection, Room* source, Room * destination) : 
	exitDirection(exitDirection),
	source(source),
	destination(destination),
	Entity(name, description, Entity::Type::Exit)
{
}



Exit::Direction Exit::GetExitDirection() const
{
	return this->exitDirection;
}

Room * Exit::GetExitDestination() const
{
	return destination;
}

Room * Exit::GetExitSource() const
{
	return source;
}

Exit::Direction Exit::ParseDirectionString(const string & direction)
{
	Direction exitDirection;
	if (direction.compare("north") == 0) {
		exitDirection = Direction::North;
	}
	else if (direction.compare("south")) {
		exitDirection = Direction::South;
	}
	else if (direction.compare("east")) {
		exitDirection = Direction::East;
	}
	else if (direction.compare("west")) {
		exitDirection = Direction::West;
	}
	else {
		exitDirection = Direction::Error;
	}
	return exitDirection;
}
