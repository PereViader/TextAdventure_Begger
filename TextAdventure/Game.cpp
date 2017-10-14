#include "Game.h"

#include <iostream>

#include "Player.h"
#include <vector>
#include <string>

#include "World.h"
#include "WorldCreator.h"

using namespace std;

Game::Game() : hasGameEnded(false)
{
	world = WorldCreator::CreateGameWorld();
	player = (Player*)world->GetChilds().at(0);
}


Game::~Game()
{
	delete world;
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
	return world -> Update();
}

void Game::PrintStartingMessage() const {
	cout << "Wellcome to zork or not!" << endl;
	cout << "This is going to be your adventure" << endl;
	cout << "Have fun!" << endl;
}


