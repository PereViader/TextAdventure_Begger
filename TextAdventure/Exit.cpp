#include "Exit.h"



Exit::Exit(const string& name, const string& description, Direction exitDirection, Room* source, Room * destination) : 
	exitDirection(exitDirection),
	source(source),
	destination(destination),
	Entity(name, description, Entity::Type::Exit)
{
}



const string Exit::GetExitDirectionString() const
{
	string exitDirectionString;

	switch (exitDirection)
	{
	case Exit::Direction::North:
		exitDirectionString = "north";
		break;
	case Exit::Direction::South:
		exitDirectionString = "south";
		break;
	case Exit::Direction::East:
		exitDirectionString = "east";
		break;
	case Exit::Direction::West:
		exitDirectionString = "west";
		break;
	case Exit::Direction::Error:
	default:
		exitDirectionString = "";
		break;
	}
	return exitDirectionString;
}

const Exit::Direction Exit::GetExitDirection() const
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
	if (direction == "north") {
		exitDirection = Direction::North;
	}
	else if (direction == "south") {
		exitDirection = Direction::South;
	}
	else if (direction == "east") {
		exitDirection = Direction::East;
	}
	else if (direction == "west") {
		exitDirection = Direction::West;
	}
	else {
		exitDirection = Direction::Error;
	}
	return exitDirection;
}
