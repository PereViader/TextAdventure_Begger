#pragma once

#include <vector>
#include <string>

using namespace std;





class PlayerAction
{
public:
	enum Type {
		Error,
		Quit,
		Beg,
		Take,
		Inventory,
		Look,
		Buy,
		Go,
		Eat,
	};

	PlayerAction(PlayerAction::Type, vector<string>);
	PlayerAction(PlayerAction::Type);

	PlayerAction::Type GetActionType() const;
	vector<string> GetActionParameters() const;

protected:
	PlayerAction::Type actionType;
	vector<string> parameters;


};



