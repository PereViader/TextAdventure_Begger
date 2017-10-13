#include "PlayerInput.h"

#include <vector>
#include <string>
#include <iostream>
#include <conio.h>

#include "PlayerAction.h"
#include "PlayerActionFabric.h"

using namespace std;

const PlayerAction PlayerInput::GetPlayerAction() const {
	bool isCurrentActionReady = GatherNewInput(currentActionString);
	if (isCurrentActionReady) {
		vector<string> tokenizedAction = TokenizeString(currentActionString);
		return PlayerActionFabric::GeneratePlayerAction(tokenizedAction);
	}
	else{
		return PlayerActionFabric::GenerateNullPlayerAction();
	}
}

bool PlayerInput::GatherNewInput(string& previousInput) {
	bool thereIsInputToGather = kbhit();
	bool isInputReady = false;
	while(!isInputReady && thereIsInputToGather) {
		char newInput = getchar();
		previousInput += newInput;
		thereIsInputToGather = hbhit();
		isInputReady = newInput == '\r';
	}
	//TODO bug check
	return isInputReady;
}

vector<string> PlayerInput::TokenizeString(const string& s) const {
	vector<string> tokens;
	
	char* workingString = _strdup(s.c_str());
	char* token = nullptr;
	char* next_token = nullptr;

	char delimiters[] = " ";

	token = strtok_s(workingString, delimiters, &next_token);
	while (token) {
		tokens.push_back(token);
		token = strtok_s(nullptr,delimiters, &next_token);
	}

	delete workingString;

	return tokens;
}