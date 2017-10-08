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
	else if (verb.compare("beg") == 0) {
		playerAction = &PlayerAction(ActionType::Beg, parameters);
	}
	else if (verb.compare("buy") == 0) {
		playerAction = &PlayerAction(ActionType::Buy, parameters);
	}
	else if (verb.compare("inventory") == 0) {
		playerAction = &PlayerAction(ActionType::Inventory, parameters);
	}
	else if (verb.compare("get") == 0 || verb.compare("take") == 0) {
		playerAction = &PlayerAction(ActionType::Take, parameters);
	}
	else {
		playerAction = &PlayerAction(ActionType::Error);
	}
	
	return *playerAction;
}