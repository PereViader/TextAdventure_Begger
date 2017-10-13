#pragma once

#include <string>
#include <vector>

using namespace std;

class PlayerAction;

class PlayerInput {

public:
	const PlayerAction GetPlayerAction();

private:
	vector<string> TokenizeString(const string&) const;
	bool GatherNewInput(string& previousInput);

	
	string currentActionString;
};