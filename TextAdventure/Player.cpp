#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
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
		this -> currentRoom -> look();
	} else {
		string itemName = "";
		//TODO: join params into a single string
		
		Entity* item = currentRoom.Find(itemName,Entity::Type::Item);
		if ( item != NULL ) {
			item -> look();
		}
	}
}

void Player::ActionInventory(const PlayerAction& playerAction){
	if (associatedEntities.size() == 0) {
		cout << "I have nothing left" << endl;
	} else {
		cout << "I found these..." << endl;
		for (vector<Entity*>::const_iterator it = associatedEntities.begin(); it != associatedEntities.end(); ++it) {
			Entity * currentEntity = *it;
			cout << currentEntity -> GetName() << endl;
		}
	}
}

void Player::ActionBuy(const PlayerAction& playerAction){
	
}

void Player::ActionTake(const PlayerAction& playerAction){
	vector<string> params = playerAction.GetActionParameters();
	if (params.size() == 0) {
		cout << "What should I take?" << endl;
	} else {
		string itemName = "";
		//TODO: Join parameters to create one single string
		Item* item = currentRoom -> Find(itemName,Entity::Type::Item);
		if (item != NULL) {
			//TODO: take item from room
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
			if (currentExit.GetDirection().compare(direction)) {
				// move player to the exit room
				break;
			}
		}
	} 
	else {
		cout << "I don't know how to go there" << endl;
	}
}

void Player::ActionEat(const PlayerAction&) {
	
}