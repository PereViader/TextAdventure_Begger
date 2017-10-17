#pragma once

#include "Creature.h"
#include "Globals.h"

class PlayerAction;
class PlayerInput;
class Room;


class Player :
	public Creature
{
public:
	Player(string name, string description, Room* startingRoom);
	~Player();
	
	unsigned int GetMoney();
	bool RemoveMoney(const int&);

	virtual Frame_Return Update() override;
	
	
	//Player Actions
	void ActionBeg(const PlayerAction*);
	void ActionLook(const PlayerAction*);
	void ActionInventory(const PlayerAction*);
	void ActionBuy(const PlayerAction*);
	void ActionTake(const PlayerAction*);
	void ActionGo(const PlayerAction*);
	void ActionThrow(const PlayerAction*);
	void ActionEat(const PlayerAction*);
	void ActionHunger(const PlayerAction*);
	
private:
	void UpdateHunger();

private:
	Room * currentRoom;
	double hunger;
	int money;

	float hungerConsumptionPerSecond;
	
	PlayerInput * playerInput;
};

