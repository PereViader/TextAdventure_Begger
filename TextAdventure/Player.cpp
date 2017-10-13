#include "Player.h"

#include <iostream>
#include <string>

#include "PlayerAction.h"
#include "Room.h"
#include "Item.h"
#include "Exit.h"
#include "Shop.h"

#include <assert.h>

using namespace std;

Player::Player(Room* startingRoom) : currentRoom(startingRoom), hunger(100), money(0)
{
	playerInput = new PlayerInput();
}


Player::~Player()
{
	delete playerInput;
}

virtual void Player::Update() {
	PlayerAction playerAction = playerInput.GetPlayerAction();
		
	switch(playerAction.GetActionType()) {
	case PlayerAction::Type::None:
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
	case PlayerAction::Type::Error:
	default:
		cout << "I don't know how to do that" << endl;
	}
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


void Player::ActionBeg(const PlayerAction& playerAction) {
	vector<string> params = playerAction.GetActionParameters();
	if (params.size() > 0) {
		cout << "It's embarrasing, I don't want to beg like that" << endl;
		return;
	} 
	
	// search room for npcs and such
}

void Player::ActionLook(const PlayerAction& playerAction){
	vector<string> params = playerAction.GetActionParameters();
	if (params.size() == 0) {
		currentRoom -> Look();
	} else {
		string itemName = playerAction.GetActionParametersAsString();
		Entity* item = currentRoom -> Find(itemName,Entity::Type::item);
		if ( item != nullptr ) {
			item -> Look();
		}
	}
}

void Player::ActionInventory(const PlayerAction& playerAction){
	if (childEntities.size() == 0) {
		cout << "I have nothing left" << endl;
	} else {
		cout << "I found these..." << endl;
		for (vector<Entity*>::const_iterator it = childEntities.begin(); it != childEntities.end(); ++it) {
			Entity * currentEntity = *it;
			cout << currentEntity -> GetName() << endl;
		}
	}
}

void Player::ActionBuy(const PlayerAction& playerAction){
	if (money == 0) {
		cout << "I don't have any money left" << endl;
		
	} 
	else if (currentRoom->GetRoomType() != Room::Shop) {
		cout << "I can only buy things in a shop" << endl;
	}
	else {
		Shop* shop = (Shop*)currentRoom;
		string itemNameToBuy = playerAction.GetActionParametersAsString();
		Item* item = (Item*)shop->Find(itemNameToBuy, Entity::Type::item);
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

void Player::ActionTake(const PlayerAction& playerAction){
	if (playerAction.GetActionParameters().size() == 0) {
		cout << "What should I take?" << endl;
	} else {
		string itemName = playerAction.GetActionParametersAsString();
		Item* item = (Item*)currentRoom -> Find(itemName,Entity::Type::item);
		if (item != nullptr) {
			item->ChangeParentTo(this);
			cout << "You took the " << item->GetName() << endl;
		}
	}
}

void Player::ActionGo(const PlayerAction& playerAction){
	vector<string> params = playerAction.GetActionParameters();
	if (params.size() == 0) {
		cout << "I should first decide where to go" << endl;
	}
	else if (params.size() == 1){
		string direction = params[0];
		vector<Exit*> exits = currentRoom -> GetExits();
		for (vector<Exit*>::const_iterator it = exits.begin(); it != exits.end(); ++it) {
			Exit* currentExit = *it;
			if (currentExit->GetExitDirection() == Exit::ParseDirectionString(direction)) {
				this->currentRoom = currentExit->GetExitDestination();
				break;
			}
		}
	} 
	else {
		cout << "I don't know how to go there" << endl;
	}
}

void Player::ActionEat(const PlayerAction& playerAction) {
	if(playerAction.GetActionParameters().size() == 0) {
		cout << "What should I eat?" << endl;
	} else {
		string foodName = playerAction.GetActionParametersAsString();
		Item* item = Find(foodName,Item::Type::Food);
		if ( item == nullptr ) {
			cout << "I don't have anything like that" << endl;
		} else {
			Food* food = (Food*)item;
			hunger += food -> GetPower();
			
		}
	}
}

void Player::Look() const
{
	cout << description << endl;
}
