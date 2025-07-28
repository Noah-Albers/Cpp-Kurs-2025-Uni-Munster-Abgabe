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

Alien::Alien(const int x, const int y, const int lifes) :
	PropMoveable(2, VerticalDirection::NONE, HorizontalDirection::RIGHT),
	PropSprite("assets/sprites/alien_default.png", 64, 64, 0.5),
	shieldSprite("assets/sprites/Alien_Shield.png", 64, 64, 1, true, 0.5)
    {
	shieldSprite.getSprite().setOrigin({32,32});
	shieldSprite.getSprite().setPosition(sf::Vector2f(x, y));
	shieldSprite.getSprite().setRotation(sf::degrees(180));

    // Positions the sprite
	sprite.setOrigin({32,32});
    sprite.setPosition(sf::Vector2f(x, y));
	sprite.setRotation(sf::degrees(180));

	this->lifes = lifes;
}
Alien::~Alien() {}


void Alien::update(float time_passed){
	this->updatePosition(time_passed);
	shieldSprite.getSprite().setPosition(sprite.getPosition());
	shieldSprite.updateSprite(time_passed);
}

sf::Vector2f Alien::getPosition() {
	return sprite.getPosition();
}

void Alien::setPosition(sf::Vector2f pos){
	if(pos.x < 0) this->changeDirection();
	if(pos.x > constants::GAME_WIDTH) this->changeDirection();
	if(pos.y < 0) pos.y = 0;
	if(pos.y > constants::GAME_HEIGHT) pos.y = constants::GAME_HEIGHT;
	
	sprite.setPosition(pos);
	shieldSprite.getSprite().setPosition(pos);
}


void Alien::changeDirection() {
	if (h_dir == HorizontalDirection::RIGHT)
		setHorizontalDirection(HorizontalDirection::LEFT);
	else
		setHorizontalDirection(HorizontalDirection::RIGHT);
}

sf::Sprite Alien::getShieldSprite() {
	return shieldSprite.getSprite();
}

void Alien::removeLife() {
	lifes--;
}

int Alien::getLifes() {
	return lifes;
}
