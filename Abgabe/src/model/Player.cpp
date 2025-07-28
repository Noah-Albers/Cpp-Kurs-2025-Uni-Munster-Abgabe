/*
 * Player.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#include "Player.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include "Constants.hpp"
#include "properties/PropMoveable.h"
#include "properties/PropSprite.h"

Player::Player() :
	PropMoveable(4),
	PropSprite("assets/sprites/player_default.png", 48, 48)
    {
		
    // Positions the sprite
	sprite.setOrigin({24,24});
    sprite.setPosition({0, constants::GAME_HEIGHT});
}
Player::~Player() {}


void Player::update(float time_passed){
	this->updatePosition(time_passed);
}

sf::Vector2f Player::getPosition() {
	return sprite.getPosition();
}

void Player::setPosition(sf::Vector2f pos){
	// Ensures the player stays in the view
	if(pos.x < 0) pos.x = 0;
	if(pos.x > constants::GAME_WIDTH) pos.x = constants::GAME_WIDTH;
	if(pos.y < 0) pos.y = 0;
	if(pos.y > constants::GAME_HEIGHT) pos.y = constants::GAME_HEIGHT;
	
	sprite.setPosition(pos);
}

