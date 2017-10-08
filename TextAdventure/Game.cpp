#include "Game.h"

#include <iostream>
#include <sstream>

#include "PlayerActionFabric.h"

Game::Game()
{
}


Game::~Game()
{
}

void Game::Execute() {
	PrintStartingMessage();
	bool hasGameEnded = false;
	while (!hasGameEnded) {
		hasGameEnded = ExecuteGameFrame();
	}
	cout << "Bye!" << endl;
}

bool Game::ExecuteGameFrame() {
	bool hasGameEnded = false;
	PlayerAction playerAction = GetNextPlayerAction();

	switch (playerAction.GetActionType()) {
	case ActionType::Load:
		break;
	case ActionType::Save:
		break;
	case ActionType::Quit:
		hasGameEnded = true;
		break;
	case ActionType::Beg:
		break;
	case ActionType::Get:
		break;
	case ActionType::Inventory:
		break;
	case ActionType::Look:
		break;
	case ActionType::Buy:
		break;
	case ActionType::Error:
	default:
		cout << "We could not understand you" << endl;
	}

	return hasGameEnded;
}

void Game::PrintStartingMessage() const {
	cout << "Wellcome to zork or not!" << endl;
	cout << "This is going to be your adventure" << endl;
	cout << "Have fun!" << endl;
}

const PlayerAction Game::GetNextPlayerAction() const {
	vector<string> playerInput;
	do {
		playerInput = AskForInput();
	} while (playerInput.size() == 0);
	return PlayerActionFabric::GeneratePlayerAction(playerInput);
}

const vector<string> Game::AskForInput() const {
	string playerInput;
	cout << "> ";
	getline(cin, playerInput);
	return TokenizeString(playerInput);
}

vector<string> Game::TokenizeString(const string& s) const {
	vector<string> tokens;
	
	char* workingString = _strdup(s.c_str());
	char* token = NULL;
	char* next_token = NULL;

	char delimiters[] = " ";

	token = strtok_s(workingString, delimiters, &next_token);
	while (token) {
		tokens.push_back(token);
		token = strtok_s(NULL,delimiters, &next_token);
	}

	delete workingString;

	return tokens;
}
