#include "Exit.h"



Exit::Exit(ExitDirection exitDirection, Room* source, Room * destination) : 
	exitDirection(exitDirection),
	source(source),
	destination(destination)
{
}



Exit::ExitDirection Exit::GetExitDirection() const
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

Exit::ExitDirection Exit::ParseDirectionString(const string & direction)
{
	ExitDirection exitDirection;
	if (direction.compare("north") == 0) {
		exitDirection = ExitDirection::North;
	}
	else if (direction.compare("south")) {
		exitDirection = ExitDirection::South;
	}
	else if (direction.compare("east")) {
		exitDirection = ExitDirection::East;
	}
	else if (direction.compare("west")) {
		exitDirection = ExitDirection::West;
	}
	else {
		exitDirection = ExitDirection::Error;
	}
	return exitDirection;
}
