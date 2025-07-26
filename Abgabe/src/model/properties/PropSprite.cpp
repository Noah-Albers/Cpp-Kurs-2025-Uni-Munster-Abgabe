/*
 * PropSprite.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#include "PropSprite.h"

PropSprite::PropSprite(const std::filesystem::path& filename, const int size_x, const int size_y) : 
	texture(),
    sprite(texture) {
	
	// load texture
    if (!texture.loadFromFile(filename))
        throw std::invalid_argument("Spritesheet not found");
    // set up sprite
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect({0, 0}, {size_x, size_y}));
}

PropSprite::~PropSprite() {}


sf::Sprite PropSprite::getSprite() {
	return sprite;
}


