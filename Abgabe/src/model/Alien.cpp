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
	shieldSprite("assets/sprites/Alien_Shield.png", 64, 64, 0.5)
    {
	shieldSprite.getSpriteReference().setOrigin({32,32});
	shieldSprite.getSpriteReference().setPosition(sf::Vector2f{x, y});
	shieldSprite.getSpriteReference().setRotation(sf::degrees(180));

    // Positions the sprite
	sprite.setOrigin({32,32});
    sprite.setPosition(sf::Vector2f(x, y));
	sprite.setRotation(sf::degrees(180));

	animation_clock.restart();
	frame_index = 0;
	this->lifes = lifes;
}
Alien::~Alien() {}


void Alien::update(){
	this->updatePosition();
	shieldSprite.getSpriteReference().setPosition(sprite.getPosition());
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
	shieldSprite.getSpriteReference().setPosition(pos);
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

void Alien::nextSprite() {
    if (animation_clock.getElapsedTime().asSeconds() > constants::ANIMATION_TIME) {
        frame_index++;
        shieldSprite.setFrame(frame_index);
        animation_clock.restart();
    }
}

void Alien::removeLife() {
	lifes--;
}

int Alien::getLifes() {
	return lifes;
}
