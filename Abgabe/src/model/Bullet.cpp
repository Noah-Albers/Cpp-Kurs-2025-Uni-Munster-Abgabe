/*
 * Bullet.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#include "Bullet.h"
#include "properties/PropMoveable.h"
#include "properties/PropSprite.h"
#include <SFML/System/Vector2.hpp>

#include "../assets/AssetMappings.h"

Bullet::Bullet(const int x, const int y) :
	PropMoveable(10, VerticalDirection::UP),
	PropSprite(ASSETS_SPRITE_PLAYER_BULLET)
{
	sprite.setPosition(sf::Vector2f(x,y));
}

Bullet::~Bullet() {}

sf::Vector2f Bullet::getPosition() {
	return sprite.getPosition();
}

void Bullet::setPosition(sf::Vector2f pos){
	sprite.setPosition(pos);
}
