/*
 * AlienBullet.cpp
 *
 *  Created on: 28.07.2025
 *      Author: Olly
 */

#include "AlienBullet.h"
#include "properties/PropAnimatedSprite.h"
#include "properties/PropMoveable.h"
#include <SFML/System/Vector2.hpp>
#include "Constants.hpp"
#include "../assets/AssetMappings.h"

AlienBullet::AlienBullet(const int x, const int y) :
	PropMoveable(constants::ALIEN_BULLET_SPEED, VerticalDirection::DOWN),
	PropAnimatedSprite(ASSETS_SPRITE_ALIEN_BULLET, constants::ANIMATION_TIME, true, 0.8)
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

void AlienBullet::update(float time_passed) {
	updateSprite(time_passed);
	updatePosition(time_passed);
}
