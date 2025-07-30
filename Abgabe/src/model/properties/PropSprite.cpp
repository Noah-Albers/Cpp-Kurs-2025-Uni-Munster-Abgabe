/*
 * PropSprite.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#include "PropSprite.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

PropSprite::PropSprite(const std::filesystem::path& filename, const int size_x, const int size_y, const float scale, const bool centerOrigin) : 
	texture(),
    sprite(texture) {
	
	// load texture
    if (!texture.loadFromFile(filename))
        throw std::invalid_argument("Spritesheet not found");
    // set up sprite
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect({0, 0}, {size_x, size_y}));
    sprite.scale({scale, scale});
    if(centerOrigin)
    	sprite.setOrigin(sf::Vector2f((float)size_x/2.0, (float)size_y/2.0));
}

const sf::Sprite& PropSprite::getSprite() const {
	return sprite;
}

bool PropSprite::isCollidingWith(const PropSprite& object, float margin) const {
	auto thisBounds = sprite.getGlobalBounds();
	auto objectBounds = object.getSprite().getGlobalBounds();
	
	if(margin > 0){		
		thisBounds.position.x += margin;
		thisBounds.position.y += margin;
		thisBounds.size.x -= margin*2;
		thisBounds.size.y -= margin*2;
		objectBounds.position.x += margin;
		objectBounds.position.y += margin;
		objectBounds.size.x -= margin*2;
		objectBounds.size.y -= margin*2;
	}

	return thisBounds.findIntersection(objectBounds).has_value();
}

void PropSprite::setFrame(int index){
	// Ensures that it rotates after the maximum index
	index = index % getFrameAmount();
	
	sprite.setTextureRect(sf::IntRect({
		sprite.getTextureRect().size.x * index,
		sprite.getTextureRect().position.y
	}, sprite.getTextureRect().size));
}

int PropSprite::getFrameAmount(){
	return sprite.getTexture().getSize().x/sprite.getTextureRect().size.x;
}

int PropSprite::getFrame(){
	return sprite.getTextureRect().position.x/sprite.getTextureRect().size.x;
}
