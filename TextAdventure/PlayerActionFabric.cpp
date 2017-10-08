#include "PlayerActionFabric.h"


const PlayerAction PlayerActionFabric::GeneratePlayerAction(const vector<string>& playerInput) {
	PlayerAction playerAction;

	string verb = playerInput[0];
	vector<string> parameters(playerInput.begin() + 1, playerInput.end());
	
	if (verb.compare("look") == 0) {
		playerAction.actionType = ActionType::Look;
	}
	else if (verb.compare("quit") == 0 || verb.compare("exit") == 0) {
		playerAction.actionType = ActionType::Quit;
	}
	else if (verb.compare("load") == 0) {
		playerAction.actionType = ActionType::Load;
	}
	else if (verb.compare("save") == 0) {
		playerAction.actionType = ActionType::Save;
	}
	else if (verb.compare("beg") == 0) {
		playerAction.actionType = ActionType::Beg;
	}
	else if (verb.compare("buy") == 0) {
		playerAction.actionType = ActionType::Buy;
	}
	else if (verb.compare("get") == 0 || verb.compare("take") == 0) {
		playerAction.actionType = ActionType::Get;
	}

	if (playerAction.actionType != ActionType::Error)
		playerAction.parameters = parameters;
	
	return playerAction;
}