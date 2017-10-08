#pragma once

#include <vector>
#include <string>

using namespace std;

enum ActionType {
	Error,
	Quit,
	Save,
	Load,
	Beg,
	Get,
	Inventory,
	Look,
	Buy,
};



class PlayerAction
{
protected:
	ActionType actionType;
	vector<string> parameters;

public:
	PlayerAction(ActionType, vector<string>);
	PlayerAction(ActionType);

	ActionType GetActionType() const;
	vector<string> GetActionParameters() const;


};



