/*
 * Player.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Olly
 */

#include "Alien.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include "Constants.hpp"
#include "properties/PropMoveable.h"
#include "properties/PropSprite.h"

Alien::Alien(const int x, const int y) :
	PropMoveable(2, VerticalDirection::NONE, HorizontalDirection::RIGHT),
	PropSprite("assets/sprites/alien_default.png", 48, 48)
    {
		
    // Positions the sprite
	sprite.setOrigin({24,24});
    sprite.setPosition({x, y});
}
Alien::~Alien() {}


void Alien::update(){
	this->updatePosition();
}

sf::Vector2f Alien::getPosition() {
	return sprite.getPosition();
}

void Alien::setPosition(sf::Vector2f pos){
	// Ensures the player stays in the view
	if(pos.x < 0) pos.x = 0;
	if(pos.x > constants::VIEW_WIDTH) pos.x = constants::VIEW_WIDTH;
	if(pos.y < 0) pos.y = 0;
	if(pos.y > constants::VIEW_HEIGHT) pos.y = constants::VIEW_HEIGHT;
	
	sprite.setPosition(pos);
}

