#include "PlayerActionFabric.h"

const PlayerAction* PlayerActionFabric::GenerateNullPlayerAction() {
	return new PlayerAction(PlayerAction::Type::None);
}

const PlayerAction* PlayerActionFabric::GeneratePlayerAction(const vector<string>& playerInput) {
	PlayerAction * playerAction = nullptr;

	string verb = playerInput[0];
	vector<string> parameters(playerInput.begin() + 1, playerInput.end());
	
	if (verb == "look") {
		playerAction = new PlayerAction(PlayerAction::Type::Look, parameters);
	}
	else if (verb == "quit" || verb == "exit") {
		playerAction = new PlayerAction(PlayerAction::Type::Quit, parameters);
	}
	else if (verb == "beg") {
		playerAction = new PlayerAction(PlayerAction::Type::Beg, parameters);
	}
	else if (verb == "buy") {
		playerAction = new PlayerAction(PlayerAction::Type::Buy, parameters);
	}
	else if (verb == "inventory") {
		playerAction = new PlayerAction(PlayerAction::Type::Inventory, parameters);
	}
	else if (verb == "go") {
		playerAction = new PlayerAction(PlayerAction::Type::Go, parameters);
	}
	else if (verb == "eat") {
		playerAction = new PlayerAction(PlayerAction::Type::Eat, parameters);
	}
	else if (verb == "get" || verb == "take") {
		playerAction = new PlayerAction(PlayerAction::Type::Take, parameters);
	}
	else if (verb == "throw") {
		playerAction = new PlayerAction(PlayerAction::Type::Throw, parameters);
	}
	else {
		playerAction = new PlayerAction(PlayerAction::Type::Error);
	}
	
	return playerAction;
}
