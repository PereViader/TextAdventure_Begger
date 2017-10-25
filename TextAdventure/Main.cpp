#include <iostream>
#include <chrono>
#include <thread>

#include "Game.h"

int main(void) {
	Game * game = new Game();
	game->Execute();
	delete game;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	return 0;
}