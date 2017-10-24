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
#include "Time.h"
#include "Street.h"
#include "ItemContainer.h"

#include <stdlib.h>


#include <assert.h>


using namespace std;

Player::Player(string name, string description, Room* startingRoom) :
	hunger(100),
	money(0),
	hungerConsumptionPerSecond(0.1f),
	playerInput(new PlayerInput()), 
	Creature(name, description, startingRoom, Creature::Type::Player)
{
	srand(6); // set seed for debugging purposes
}


Player::~Player()
{
	delete playerInput;
}

Frame_Return Player::Update() {

	Frame_Return frame_return = UpdateHunger();

	if (frame_return != Frame_Return::Continue) return frame_return;

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
		break;
	case PlayerAction::Type::Hunger:
		ActionHunger(playerAction);
		break;
	case PlayerAction::Type::Money:
		ActionMoney(playerAction);
		break;
	case PlayerAction::Type::Open:
		ActionOpen(playerAction);
		break;
	case PlayerAction::Type::Error:
	default:
		cout << "I don't know how to do that" << endl;
	}
	delete playerAction;
	return frame_return;
}

Frame_Return Player::UpdateHunger()
{
	Frame_Return ret = Frame_Return::Continue;
	hunger -= Time::GetDeltaTime() * hungerConsumptionPerSecond;
	if (hunger < 0) {
		hunger = 0;
		ret = Frame_Return::Stop;
		cout << endl << endl << "You died of hunger" << endl;
	}
	return ret;
}

unsigned int Player::GetMoney()
{
	return money;
}

bool Player::RemoveMoney(const int & amountToRemove)
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
	else if (GetCurrentRoom()->GetRoomType() == Room::Type::Street) {
		Street* street = (Street*)GetCurrentRoom();
		float randomValue = ((float)(rand() % 101)) / 100.0f;
		bool hasSucceded = randomValue <= street->GetPlayerBegSuccessRate();
		if (hasSucceded) {
			money += 1;
			cout << "A kind person gave you a coin" << endl;
		}
		else {
			cout << "They ignored you" << endl;
		}
	}
	
}

void Player::ActionLook(const PlayerAction* playerAction){
	vector<string> params = playerAction->GetActionParameters();
	if (params.size() == 0) {
		GetCurrentRoom() -> Look();
	} else {
		string itemName = playerAction->GetActionParametersAsString();
		Entity* item = GetCurrentRoom()-> Find(itemName,Entity::Type::Item);
		if ( item == nullptr ) {
			cout << "There's nothing like that around here" << endl;
		}
		else {
			item->Look();
		}
	}
}

void Player::ActionInventory(const PlayerAction* playerAction){
	if (playerAction->GetActionParameters().size() == 0) {
		if (childEntities.size() == 0)
		{
			cout << "I have nothing left" << endl;
		}
		else {
			cout << "I found these..." << endl;
			for (vector<Entity*>::const_iterator it = childEntities.begin(); it != childEntities.end(); ++it) {
				Entity * currentEntity = *it;
				cout << currentEntity->GetName() << endl;
			}
		}
	} 
	else {
		string itemName = playerAction->GetActionParametersAsString();
		Item* item = (Item*)Find(itemName, Entity::Type::Item);

		if (item == nullptr) {
			cout << "I don't have that" << endl;
		}
		else {
			item->Look();
		}
	}
}

void Player::ActionBuy(const PlayerAction* playerAction){
	if (money == 0) {
		cout << "I don't have any money left" << endl;
	}
	else if (GetCurrentRoom()->GetRoomType() != Room::Type::Shop) {
		cout << "I can only buy things in a shop" << endl;
	}
	else {
		Shop* shop = (Shop*)GetCurrentRoom();
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
		Item* item = (Item*)GetCurrentRoom()-> Find(itemName,Entity::Type::Item);
		if (item == nullptr) {
			cout << "You can't see that around here" << endl;
		}
		else {
			item->AttachToParent(this);
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
		vector<Exit*> exits = GetCurrentRoom()-> GetExits();
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
			Room* destination = exitToTake->GetExitDestination();
			Move(destination);
			GetCurrentRoom()->Look();
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
			itemToThrow->AttachToParent(GetCurrentRoom());
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

void Player::ActionHunger(const PlayerAction * playerAction)
{
	if (playerAction->GetActionParameters().size() > 0) {
		cout << "I don't know how to do that" << endl;
	}
	else {
		assert(hunger > 0);
		if (hunger >= 100) {
			cout << "I couldn't be any more happy" << endl;
		}
		else if (hunger >= 80) {
			cout << "I feel just fine. Time to get going" << endl;
		}
		else if (hunger >= 70) {
			cout << "I am just fine" << endl;
		}
		else if (hunger >= 50) {
			cout << "My stomach could be better" << endl;
		} 
		else if ( hunger >= 40) {
			cout << "Time to eat" << endl;
		}
		else if (hunger >= 30) {
			cout << "Food... where is it" << endl;
		}
		else if (hunger >= 20) {
			cout << "I really need to eat" << endl;
		}
		else if (hunger >= 10) {
			cout << "I feel like I am at the brink of death. Hunger fills me" << endl;
		}
		else if (hunger > 0) {
			cout << "I can't take it any more. Bye." << endl;
		}

		cout << "My life total is " << hunger << "/100" << endl;
	}
}

void Player::ActionMoney(const PlayerAction * playerAction)
{
	if (playerAction->GetActionParameters().size() > 0) {
		cout << "I don't know how to do that" << endl;
	}
	else {
		if (money == 0)
			cout << "I don't have any money" << endl;
		else
			cout << "I have " << money << " coins" << endl;
	}
}

void Player::ActionOpen(const PlayerAction * playerAction)
{
	if (playerAction->GetActionParameters().size() == 0) {
		cout << "What should I open?" << endl;
	}
	else {
		string itemName = playerAction->GetActionParametersAsString();
		Item* item = (Item*)Find(itemName, Entity::Type::Item);
		if (item == nullptr) {
			cout << "I don't have anything like that" << endl;
		}
		else if (item->GetItemType() != Item::Type::ItemContainer) {
			cout << "I can't open that" << endl;
		}
		else {
			ItemContainer * itemContainer = (ItemContainer*)item;
			vector<Item*> itemsInside = itemContainer->GetItemsInside();
			if (itemsInside.size() == 0) {
				cout << "It's empty" << endl;
			}
			else {
				for (Item* i : itemsInside) {
					AttachChild(i);
					cout << "You found: " << i->GetName() << endl;
				}
			}
		}
	}
}