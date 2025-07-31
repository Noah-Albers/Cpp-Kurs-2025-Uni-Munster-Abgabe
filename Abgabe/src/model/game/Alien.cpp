/*
 * Alien.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Olly
 */

#include "Alien.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include "AlienShield.h"
#include "../Constants.hpp"
#include "../properties/PropMoveable.h"
#include "../properties/PropSprite.h"

#include "../../assets/AssetMappings.h"

Alien::Alien(const int x, const int y, const int lifes, const float speed) :
	PropMoveable(speed, VerticalDirection::NONE, HorizontalDirection::RIGHT),
	PropSprite(ASSETS_SPRITE_ALIEN, true),
	shield(nullptr),
	lifes(lifes)
    {

    // Creates a shield if the alien has more than one life
    if(lifes > 1)
    	// Allocates a new shield sprite for the alien
		shield = new AlienShield();
	
	// Positions the alien
	setPosition(sf::Vector2f(x, y));
}

Alien::~Alien(){
	// Ensures the shield is deallocated
	deleteShield();
}

void Alien::update(const float time_passed){
	this->updatePosition(time_passed);
	
	if(hasShield())
		shield->updateSprite(time_passed);
}


void Alien::setPosition(const sf::Vector2f newPos){
	auto pos = sf::Vector2f(newPos);
	
	// Clamps position
	// Does not clamp upper position to allow for smooth transition
	if(pos.x < 0) pos.x = 0;
	if(pos.x > constants::GAME_WIDTH) pos.x = constants::GAME_WIDTH;
	if(pos.y > constants::GAME_HEIGHT) pos.y = constants::GAME_HEIGHT;
	
	sprite.setPosition(pos);
	
	if(hasShield())
		shield->setPosition(pos);
}

void Alien::changeDirection() {
	if (h_dir == HorizontalDirection::RIGHT)
		setHorizontalDirection(HorizontalDirection::LEFT);
	else
		setHorizontalDirection(HorizontalDirection::RIGHT);
}

void Alien::removeLife() {
	if(lifes <= 0) return;
	
	lifes--;
	
	// Removes the shield
	if(lifes == 1)
		deleteShield();
}

void Alien::deleteShield(){
	if(!hasShield()) return;
	delete shield;
	shield = nullptr;
}

// #region Getters/Setters

const int Alien::getLifes() const { return lifes; };
const bool Alien::hasShield() const { return shield != nullptr; };
const sf::Sprite& Alien::getShieldSprite() const { return shield->getSprite(); };
const sf::Vector2f Alien::getPosition() const { return sprite.getPosition(); };

// #endregion
