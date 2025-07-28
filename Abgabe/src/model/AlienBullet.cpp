/*
 * AlienBullet.cpp
 *
 *  Created on: 28.07.2025
 *      Author: Olly
 */

#include "AlienBullet.h"
#include "properties/PropMoveable.h"
#include "properties/PropSprite.h"
#include <SFML/System/Vector2.hpp>

AlienBullet::AlienBullet(const int x, const int y) :
	PropMoveable(10, VerticalDirection::DOWN),
	PropSprite("assets/sprites/Alien_Bullet.png", 18, 38)
{
	sprite.setPosition(sf::Vector2f(x,y));
}

AlienBullet::~AlienBullet() {}

sf::Vector2f AlienBullet::getPosition() {
	return sprite.getPosition();
}

void AlienBullet::setPosition(sf::Vector2f pos){
	sprite.setPosition(pos);
}
