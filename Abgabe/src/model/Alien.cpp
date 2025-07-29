/*
 * Alien.cpp
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

#include "../assets/AssetMappings.h"

Alien::Alien(const int x, const int y, const int lifes) :
	PropMoveable(2, VerticalDirection::NONE, HorizontalDirection::RIGHT),
	PropSprite(ASSETS_SPRITE_ALIEN, true),
	shieldSprite(ASSETS_SPRITE_ALIEN_SHIELD, 1, true, true)
    {
	shieldSprite.getSprite().setPosition(sf::Vector2f(x, y));
	shieldSprite.getSprite().setRotation(sf::degrees(180));

    // Positions the sprite
    sprite.setPosition(sf::Vector2f(x, y));
	sprite.setRotation(sf::degrees(180));

	this->lifes = lifes;
}


void Alien::update(float time_passed){
	this->updatePosition(time_passed);
	shieldSprite.getSprite().setPosition(sprite.getPosition());
	shieldSprite.updateSprite(time_passed);
}

sf::Vector2f Alien::getPosition() {
	return sprite.getPosition();
}

void Alien::setPosition(sf::Vector2f pos){
	// Clamps position
	if(pos.x < 0) pos.x = 0;
	if(pos.x > constants::GAME_WIDTH) pos.x = constants::GAME_WIDTH;
	if(pos.y < 0) pos.y = 0;
	if(pos.y > constants::GAME_HEIGHT) pos.y = constants::GAME_HEIGHT;
	
	// Changes alien direction when at the sides
	if(pos.x == 0 || pos.x == constants::GAME_HEIGHT)
		changeDirection();
	
	sprite.setPosition(pos);
	shieldSprite.getSprite().setPosition(pos);
}

void Alien::changeDirection() {
	if (h_dir == HorizontalDirection::RIGHT)
		setHorizontalDirection(HorizontalDirection::LEFT);
	else
		setHorizontalDirection(HorizontalDirection::RIGHT);
}

void Alien::removeLife() {
	lifes--;
}



// #region Getters/Setters

int Alien::getLifes() { return lifes; };
sf::Sprite Alien::getShieldSprite() { return shieldSprite.getSprite(); };

// #endregion
