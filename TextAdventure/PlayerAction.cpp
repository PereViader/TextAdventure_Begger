#include "PlayerAction.h"

#include <vector>
#include <string>

using namespace std;

PlayerAction::PlayerAction(PlayerAction::Type actionType, vector<string> parameters) : actionType(actionType) , parameters(parameters){
}

PlayerAction::PlayerAction(PlayerAction::Type actionType) : actionType(actionType) {
}

const PlayerAction::Type PlayerAction::GetActionType() const {
	return actionType;
}

const vector<string> PlayerAction::GetActionParameters() const {
	return parameters;
}

const string PlayerAction::GetActionParametersAsString() const
{
	string paramString("");

	if (parameters.size() > 0) {
		paramString += parameters[0];
		for (size_t index = 1; index < parameters.size(); ++index) {
			paramString += " "+parameters[index];
		}
	}
	return paramString;
}
