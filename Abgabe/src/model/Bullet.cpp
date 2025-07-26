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

Bullet::Bullet(const int x, const int y) :
	PropMoveable(2, VerticalDirection::UP),
	PropSprite("assets/sprites/bullet_default.png", 32, 32)
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
