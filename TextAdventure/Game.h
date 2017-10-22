#pragma once

#include <vector>
#include <string>

#include "Globals.h"

class PlayerAction;
class Player;
class World;

using namespace std;

class Game
{
public:
	Game();
	virtual ~Game();
	void Execute();

private:
	void PrintStartingMessage() const;
	Frame_Return Update();

	World * world;
	
	bool hasGameEnded;
};

