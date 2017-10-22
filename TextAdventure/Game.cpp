#include "Game.h"

#include <iostream>

#include "Player.h"
#include <vector>
#include <string>
#include <stack>

#include "World.h"
#include "WorldCreator.h"
#include "Time.h"

using namespace std;

Game::Game() : hasGameEnded(false)
{
	world = WorldCreator::CreateGameWorld();
}


Game::~Game()
{
	delete world;
}

void Game::Execute() {
	PrintStartingMessage();
	Frame_Return ret;
	do {
		Time::UpdateClock();
		ret = Update();
	} while(ret == Frame_Return::Continue);
	cout << "Bye!" << endl;
}

Frame_Return Game::Update() {
	Frame_Return update_return = Frame_Return::Continue;
	stack<Entity*> entityStack;
	entityStack.push(world);
	while (update_return == Frame_Return::Continue && entityStack.size() > 0)
	{
		Entity* currentEntityToUpdate = entityStack.top();
		entityStack.pop();
		update_return = currentEntityToUpdate->Update();
		vector<Entity*> entityChilds = currentEntityToUpdate->GetChilds();

		for (vector<Entity*>::reverse_iterator it = entityChilds.rbegin(); it != entityChilds.rend(); ++it) {
			entityStack.push(*it);
		}
	}
	return update_return;
}

void Game::PrintStartingMessage() const {
	cout << "This is going to be your adventure" << endl;
	cout << "You are a begger" << endl;
	cout << "Survive" << endl;
	cout << endl;
}


