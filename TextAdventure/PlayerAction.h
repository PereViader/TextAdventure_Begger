#pragma once

#include <vector>
#include <string>

using namespace std;

class PlayerAction
{
public:
	enum class Type {
		None,
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

	const PlayerAction::Type GetActionType() const;
	const vector<string> GetActionParameters() const;
	const string GetActionParametersAsString() const;

protected:
	const PlayerAction::Type actionType;
	const vector<string> parameters;
};



