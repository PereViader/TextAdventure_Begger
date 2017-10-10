#include "PlayerActionFabric.h"


const PlayerAction PlayerActionFabric::GeneratePlayerAction(const vector<string>& playerInput) {
	PlayerAction * playerAction = NULL;

	string verb = playerInput[0];
	vector<string> parameters(playerInput.begin() + 1, playerInput.end());
	
	if (verb.compare("look") == 0) {
		playerAction = &PlayerAction(PlayerAction::Type::Look, parameters);
	}
	else if (verb.compare("quit") == 0 || verb.compare("exit") == 0) {
		playerAction = &PlayerAction(PlayerAction::Type::Quit, parameters);
	}
	else if (verb.compare("beg") == 0) {
		playerAction = &PlayerAction(PlayerAction::Type::Beg, parameters);
	}
	else if (verb.compare("buy") == 0) {
		playerAction = &PlayerAction(PlayerAction::Type::Buy, parameters);
	}
	else if (verb.compare("inventory") == 0) {
		playerAction = &PlayerAction(PlayerAction::Type::Inventory, parameters);
	}
	else if (verb.compare("go") == 0) {
		playerAction = &PlayerAction(PlayerAction::Type::Go, parameters);
	}
	else if (verb.compare("eat") == 0) {
		playerAction = &PlayerAction(PlayerAction::Type::Eat, parameters);
	}
	else if (verb.compare("get") == 0 || verb.compare("take") == 0) {
		playerAction = &PlayerAction(PlayerAction::Type::Take, parameters);
	}
	else {
		playerAction = &PlayerAction(PlayerAction::Type::Error);
	}
	
	return *playerAction;
}
