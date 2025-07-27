#include <SFML/Graphics.hpp>
#include "control/Game.hpp"
#include <iostream>
#include <ostream>

int main() {
	std::cout << "hello" << std::endl;
	
	Game::getInstance().start();
    return 0;
	
}