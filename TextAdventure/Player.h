#pragma once

#include "Creature.h"
#include "Entity.h"
#include "Exit.h"
#include <vector>
#include <string>


class Player :
	public Creature
{
public:
	Player();
	~Player();
	
	void ActionBeg(const PlayerAction&);
	void ActionLook(const PlayerAction&);
	void ActionInventory(const PlayerAction&);
	void ActionBuy(const PlayerAction&);
	void ActionTake(const PlayerAction&);
	void ActionGo(const PlayerAction&);
	void ActionEat(const PlayerAction&);
	
private:

	Room * currentRoom;
	unsigned int hunger;
	unsigned int money;
	
};

