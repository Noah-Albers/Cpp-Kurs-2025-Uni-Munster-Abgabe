/*
 * AssetLoader.h
 *
 *  Created on: 27.07.2025
 *      Author: Noah
 */

#ifndef SRC_ASSETLOADER_H_
#define SRC_ASSETLOADER_H_

#include <SFML/Graphics/Font.hpp>
class AssetLoader {
public:
	AssetLoader();
	
    // Singleton access method
    static AssetLoader& getInstance();
	
	const sf::Font& getGameFont();
	
private:	
	sf::Font gameFont;
};

#endif /* SRC_ASSETLOADER_H_ */
