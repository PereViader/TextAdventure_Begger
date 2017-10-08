#include "PlayerAction.h"

PlayerAction::PlayerAction(ActionType actionType, vector<string> parameters) {
	this->actionType = actionType;
	this->parameters = parameters;
}

PlayerAction::PlayerAction(ActionType actionType) {
	this->actionType = actionType;
}


ActionType PlayerAction::GetActionType() const {
	return actionType;
}

vector<string> PlayerAction::GetActionParameters() const {
	return parameters;
}
