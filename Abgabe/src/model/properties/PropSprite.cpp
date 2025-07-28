/*
 * PropSprite.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#include "PropSprite.h"
#include <SFML/Graphics/Rect.hpp>

PropSprite::PropSprite(const std::filesystem::path& filename, const int size_x, const int size_y, const float scale) : 
	texture(),
    sprite(texture) {
	
	// load texture
    if (!texture.loadFromFile(filename))
        throw std::invalid_argument("Spritesheet not found");
    // set up sprite
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect({0, 0}, {size_x, size_y}));
    sprite.scale({scale, scale});
}

PropSprite::~PropSprite() {}


sf::Sprite PropSprite::getSprite() {
	return sprite;
}

sf::Sprite& PropSprite::getSpriteReference() { 
	return sprite;
}

//detects whether the current object collides with another
bool PropSprite::isCollidingWith(PropSprite& object){
		auto thisBounds = sprite.getGlobalBounds();
		auto objectBounds = object.getSprite().getGlobalBounds();

		return thisBounds.findIntersection(objectBounds).has_value();
		
	}

void PropSprite::setFrame(int index){
	// Ensures that it rotates after the maximum index
	int maxIndx = sprite.getTexture().getSize().x/sprite.getTextureRect().size.x;
	index = index % maxIndx;
	
	sprite.setTextureRect(sf::IntRect({
		sprite.getTextureRect().size.x * index,
		0
	}, sprite.getTextureRect().size));
}

int PropSprite::getFrame(){
	return sprite.getTextureRect().position.x/sprite.getTextureRect().size.x;
}
