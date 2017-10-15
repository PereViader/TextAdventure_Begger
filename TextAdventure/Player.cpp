#include "Player.h"

#include <iostream>
#include <string>

#include "PlayerAction.h"
#include "Room.h"
#include "Item.h"
#include "Exit.h"
#include "Shop.h"
#include "Food.h"
#include "PlayerInput.h"
#include "Creature.h"
#include "Entity.h"


#include <assert.h>


using namespace std;

Player::Player(string name, string description, Room* startingRoom) : 
	currentRoom(startingRoom), 
	hunger(100), 
	money(0), 
	playerInput(new PlayerInput()), 
	Creature(name,description,Creature::Type::Player)
{
}


Player::~Player()
{
	delete playerInput;
}

Frame_Return Player::Update() {
	Frame_Return frame_return = Frame_Return::Continue;

	const PlayerAction* playerAction = playerInput -> GetPlayerAction();
		
	switch(playerAction -> GetActionType()) {
	case PlayerAction::Type::None:
		break;
	case PlayerAction::Type::Quit:
		frame_return = Frame_Return::Stop;
		break;
	case PlayerAction::Type::Buy:
		ActionBuy(playerAction);
		break;
	case PlayerAction::Type::Look:
		ActionLook(playerAction);
		break;
	case PlayerAction::Type::Inventory:
		ActionInventory(playerAction);
		break;
	case PlayerAction::Type::Beg:
		ActionBeg(playerAction);
		break;
	case PlayerAction::Type::Eat:
		ActionEat(playerAction);
		break;
	case PlayerAction::Type::Take:
		ActionTake(playerAction);
		break;
	case PlayerAction::Type::Go:
		ActionGo(playerAction);
		break;
	case PlayerAction::Type::Throw:
		ActionThrow(playerAction);
	case PlayerAction::Type::Error:
	default:
		cout << "I don't know how to do that" << endl;
	}
	delete playerAction;
	return frame_return;
}

unsigned int Player::GetMoney()
{
	return money;
}

bool Player::RemoveMoney(const unsigned int & amountToRemove)
{
	bool hasEnoughMoney = false;
	if (money >= amountToRemove) {
		hasEnoughMoney = true;
		money -= amountToRemove;
	}
	return hasEnoughMoney;
}


void Player::ActionBeg(const PlayerAction* playerAction) {
	vector<string> params = playerAction -> GetActionParameters();
	if (params.size() > 0) {
		cout << "It's embarrasing, I don't want to beg like that" << endl;
		return;
	} 
	
	// search room for npcs and such
}

void Player::ActionLook(const PlayerAction* playerAction){
	vector<string> params = playerAction->GetActionParameters();
	if (params.size() == 0) {
		currentRoom -> Look();
	} else {
		string itemName = playerAction->GetActionParametersAsString();
		Entity* item = currentRoom -> Find(itemName,Entity::Type::Item);
		if ( item == nullptr ) {
			cout << "There's nothing like that around here" << endl;
		}
		else {
			item->Look();
		}
	}
}

void Player::ActionInventory(const PlayerAction* playerAction){
	if (playerAction->GetActionParameters().size() > 0) {
		cout << "I don't know how to do that with my inventory" << endl;
	} 
	else if (childEntities.size() == 0) 
	{
		cout << "I have nothing left" << endl;
	} 
	else {
		cout << "I found these..." << endl;
		for (vector<Entity*>::const_iterator it = childEntities.begin(); it != childEntities.end(); ++it) {
			Entity * currentEntity = *it;
			cout << currentEntity -> GetName() << endl;
		}
	}
}

void Player::ActionBuy(const PlayerAction* playerAction){
	if (money == 0) {
		cout << "I don't have any money left" << endl;
	} 
	else if (currentRoom->GetRoomType() != Room::Type::Shop) {
		cout << "I can only buy things in a shop" << endl;
	}
	else {
		Shop* shop = (Shop*)currentRoom;
		string itemNameToBuy = playerAction->GetActionParametersAsString();
		Item* item = (Item*)shop->Find(itemNameToBuy, Entity::Type::Item);
		if (item == nullptr) {
			cout << "I can't buy that here" << endl;
		}
		else {
			bool playerBoughtItem = shop->SellItemToPlayer(this, item);
			if (playerBoughtItem) {
				cout << "You bought: " << itemNameToBuy << endl;
			}
			else {
				cout << "You didn't have enough money to buy the item" << endl;
			}
		}
	}
}

void Player::ActionTake(const PlayerAction* playerAction){
	if (playerAction->GetActionParameters().size() == 0) {
		cout << "What should I take?" << endl;
	} else {
		string itemName = playerAction->GetActionParametersAsString();
		Item* item = (Item*)currentRoom -> Find(itemName,Entity::Type::Item);
		if (item == nullptr) {
			cout << "You can't see that around here" << endl;
		}
		else {
			item->AttackToParent(this);
			cout << "You took the " << item->GetName() << endl;
		}
	}
}

void Player::ActionGo(const PlayerAction* playerAction){
	vector<string> params = playerAction->GetActionParameters();
	if (params.size() == 0) {
		cout << "I should first decide where to go" << endl;
	}
	else if (params.size() == 1){
		string direction = params[0];
		vector<Exit*> exits = currentRoom -> GetExits();
		Exit* exitToTake = nullptr;
		for (vector<Exit*>::const_iterator it = exits.begin(); it != exits.end(); ++it) {
			Exit* currentExit = *it;
			if (currentExit->GetExitDirection() == Exit::ParseDirectionString(direction)) {
				exitToTake = currentExit;
				break;
			}
		}
		if (exitToTake == nullptr) {
			cout << "I can't go that way" << endl;
		}
		else {
			Room* destination = this->currentRoom = exitToTake->GetExitDestination();
			currentRoom = destination;
		}
	} 
	else {
		cout << "I don't know how to go there" << endl;
	}
}

void Player::ActionThrow(const PlayerAction* playerAction) 
{
	if (playerAction->GetActionParameters().size() == 0) {
		cout << "What should I throw away?" << endl;
	}
	else {
		const string itemToThrowName = playerAction->GetActionParametersAsString();
		Item* itemToThrow = (Item*)Find(itemToThrowName, Entity::Type::Item);
		if (itemToThrow == nullptr)
			cout << "I can't throw away something I don't have" << endl;
		else {
			itemToThrow->AttackToParent(currentRoom);
			cout << "I threw away the " << itemToThrow -> GetName() << endl;
		}
	}
}

void Player::ActionEat(const PlayerAction* playerAction) {
	if(playerAction->GetActionParameters().size() == 0) {
		cout << "What should I eat?" << endl;
	} else {
		string foodName = playerAction->GetActionParametersAsString();
		Entity* itemEntity = Find(foodName,Entity::Type::Item);
		if (itemEntity == nullptr ) {
			cout << "I don't have anything like that" << endl;
		} else {
			Item * item = (Item*)itemEntity;
			if (item->GetItemType() != Item::Type::Food) {
				cout << "I can't eat that" << endl;
			}
			else {
				Food* food = (Food*)item;
				hunger += food->GetEnergy();
				cout << "You ate a " << food->GetName() << " that gave you " << food->GetEnergy() << " energy" << endl;
				food->DeatachFromParent();
				delete food;
			}
		}
	}
}