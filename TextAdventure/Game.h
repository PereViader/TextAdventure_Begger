#pragma once

#include <vector>
#include <string>

#include "PlayerAction.h"
#include "Player.h"
#include "World.h"

using namespace std;

class Game
{
public:
	Game();
	virtual ~Game();
	void Execute();

private:
	void PrintStartingMessage() const;
	bool ExecuteGameFrame();
	const PlayerAction GetNextPlayerAction() const;
	const vector<string> AskForInput() const;
	vector<string> TokenizeString(const string&) const;

	Player player;
	World world;
};

