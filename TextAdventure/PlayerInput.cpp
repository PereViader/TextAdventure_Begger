#include "PlayerInput.h"

#include <vector>
#include <string>
#include <iostream>
#include <conio.h>

#include "PlayerAction.h"
#include "PlayerActionFabric.h"

using namespace std;

const PlayerAction* PlayerInput::GetPlayerAction() {
	bool isCurrentActionReady = GatherNewInput(currentActionString);
	if (isCurrentActionReady) {

		vector<string> tokenizedAction = TokenizeString(currentActionString);
		currentActionString = "";
		return PlayerActionFabric::GeneratePlayerAction(tokenizedAction);
	}
	else{
		return PlayerActionFabric::GenerateNullPlayerAction();
	}
}

bool PlayerInput::GatherNewInput(string& previousInput) {
	bool thereIsInputToGather = _kbhit() != 0;
	bool isEndOfInput = false;
	while(!isEndOfInput && thereIsInputToGather) {
		char newInput = _getch();
		thereIsInputToGather = _kbhit() != 0;
		if (newInput == '\b') {
			cout << '\b';
			cout << " ";
			cout << '\b';
			if (previousInput.size() > 0)
				previousInput.pop_back();
		} else if (newInput != '\r') {
			previousInput += newInput;
			cout << newInput;
		}
		else {
			cout << endl;
			cout << "----------------------" << endl;
			isEndOfInput = true;
		}
	}
	return isEndOfInput;
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