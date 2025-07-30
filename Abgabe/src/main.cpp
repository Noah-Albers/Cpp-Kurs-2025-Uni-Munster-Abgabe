#include "control/Game.hpp"
#include <ctime>
#include <cstdlib>

int main() {
	std::srand(std::time(0)); // Seed random with current time
	
	Game game;
	
	game.start();	
    return 0;	
}