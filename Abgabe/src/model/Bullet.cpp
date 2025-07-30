/*
 * Bullet.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#include "Bullet.h"
#include <SFML/System/Vector2.hpp>

#include "../assets/AssetMappings.h"

Bullet::Bullet(const int x, const int y) :
	PropMoveable(6, VerticalDirection::UP),
	PropAnimatedSprite(ASSETS_SPRITE_PLAYER_BULLET, 0.6, true, true)
{
	sprite.setPosition(sf::Vector2f(x,y));
}

Bullet::~Bullet() {}

void Bullet::update(const float time_passed) {
	updatePosition(time_passed);
	updateSprite(time_passed);
}

// #region Getters/Setters

void Bullet::setPosition(const sf::Vector2f pos){ sprite.setPosition(pos); }
const sf::Vector2f Bullet::getPosition() const { return sprite.getPosition(); };

// #endregion