#include "Game.h"

#include <iostream>
#include <sstream>

#include "Player.h"
#include "PlayerActionFabric.h"

Game::Game() : hasGameEnded(false)
{
}


Game::~Game()
{
}

void Game::Execute() {
	PrintStartingMessage();

	Frame_Return ret;
	do {
		ret = Update();
	} while(ret == Frame_Return::Continue);
	cout << "Bye!" << endl;
}

Frame_Return Game::Update() {
	world.Update();
}

void Game::PrintStartingMessage() const {
	cout << "Wellcome to zork or not!" << endl;
	cout << "This is going to be your adventure" << endl;
	cout << "Have fun!" << endl;
}


