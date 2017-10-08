#include "PlayerActionFabric.h"


const PlayerAction PlayerActionFabric::GeneratePlayerAction(const vector<string>& playerInput) {
	PlayerAction * playerAction = NULL;

	string verb = playerInput[0];
	vector<string> parameters(playerInput.begin() + 1, playerInput.end());
	
	if (verb.compare("look") == 0) {
		playerAction = &PlayerAction(ActionType::Look, parameters);
	}
	else if (verb.compare("quit") == 0 || verb.compare("exit") == 0) {
		playerAction = &PlayerAction(ActionType::Quit, parameters);
	}
	else if (verb.compare("load") == 0) {
		playerAction = &PlayerAction(ActionType::Load, parameters);
	}
	else if (verb.compare("save") == 0) {
		playerAction = &PlayerAction(ActionType::Save, parameters);
	}
	else if (verb.compare("beg") == 0) {
		playerAction = &PlayerAction(ActionType::Beg, parameters);
	}
	else if (verb.compare("buy") == 0) {
		playerAction = &PlayerAction(ActionType::Buy, parameters);
	}
	else if (verb.compare("get") == 0 || verb.compare("take") == 0) {
		playerAction = &PlayerAction(ActionType::Get, parameters);
	}
	else {
		playerAction = &PlayerAction(ActionType::Error);
	}
	
	return *playerAction;
}