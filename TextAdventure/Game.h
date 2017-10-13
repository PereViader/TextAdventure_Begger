#pragma once

#include <vector>
#include <string>

class PlayerAction;
class Player;
class World;

using namespace std;

enum class Frame_Return {
	Continue,
	Stop,
	Error
}

class Game
{
public:
	Game();
	virtual ~Game();
	void Execute();

private:
	void PrintStartingMessage() const;
	Frame_Return Update();

	
	Player * player;
	World * world;
	
	bool hasGameEnded;
};

