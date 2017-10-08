#pragma once

#include "PlayerAction.h"
#include <vector>
#include <string>

using namespace std;

class PlayerActionFabric
{
public:
	static const PlayerAction GeneratePlayerAction(const vector<string>& playerInput);
};

