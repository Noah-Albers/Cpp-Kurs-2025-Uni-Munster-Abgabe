#include "assets/AssetLoader.h"
#include "control/Game.hpp"
#include <iostream>

int main() {
	std::cout << "hello" << std::endl;

	// Initializes the asset-loader
	AssetLoader::getInstance().getGameFont();

	Game::getInstance().start();
    return 0;
	
}