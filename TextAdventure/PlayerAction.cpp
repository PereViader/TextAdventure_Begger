#include "PlayerAction.h"

PlayerAction::PlayerAction(PlayerAction::Type actionType, vector<string> parameters) {
	this->actionType = actionType;
	this->parameters = parameters;
}

PlayerAction::PlayerAction(PlayerAction::Type actionType) {
	this->actionType = actionType;
}


PlayerAction::Type PlayerAction::GetActionType() const {
	return actionType;
}

vector<string> PlayerAction::GetActionParameters() const {
	return parameters;
}
