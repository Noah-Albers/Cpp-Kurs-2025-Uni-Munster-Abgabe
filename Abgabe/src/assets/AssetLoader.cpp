/*
 * AssetLoader.cpp
 *
 *  Created on: 27.07.2025
 *      Author: Noah
 */

#include "AssetLoader.h"
#include "AssetMappings.h"

AssetLoader& AssetLoader::getInstance() {
	static AssetLoader instance;
    return instance;
}

AssetLoader::AssetLoader() {
	// Loads the font
	if (!gameFont.openFromFile(ASSETS_FONT_DEFAULT))
        throw std::runtime_error("Failed to load Font");
}

const sf::Font& AssetLoader::getGameFont(){
	return gameFont;
};

