/*
 * Bullet.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#include "Bullet.h"
#include <SFML/System/Vector2.hpp>

#include "../../assets/AssetMappings.h"
#include "../Constants.hpp"

Bullet::Bullet(const int x, const int y) :
	PropMoveable(constants::PLAYER_BULLET_SPEED, VerticalDirection::UP),
	PropAnimatedSprite(
		ASSETS_SPRITE_PLAYER_BULLET,
		constants::ANIMATION_PLAYER_BULLET_LENGTH,
		true, true
	) {
	setPosition(sf::Vector2f(x,y));
}

Bullet::~Bullet() {}

void Bullet::update(const float timePassed) {
	updatePosition(timePassed);
	updateSprite(timePassed);
}

// #region Getters/Setters

void Bullet::setPosition(const sf::Vector2f pos){ sprite.setPosition(pos); }
const sf::Vector2f Bullet::getPosition() const { return sprite.getPosition(); };

// #endregion