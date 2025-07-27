/*
 * AssetLoader.cpp
 *
 *  Created on: 27.07.2025
 *      Author: Noah
 */

#include "AssetLoader.h"

AssetLoader& AssetLoader::getInstance() {
	static AssetLoader instance;
    return instance;
}

AssetLoader::AssetLoader() {
	// Loads the font
	if (!gameFont.openFromFile("assets/fonts/DejaVuSansMono.ttf"))
        throw std::runtime_error("Failed to load Font");
}

const sf::Font& AssetLoader::getGameFont(){
	return gameFont;
};

