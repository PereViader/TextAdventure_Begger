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
public:
	vector<string> parameters;
	ActionType actionType;
};



