/*
 * AlienBullet.cpp
 *
 *  Created on: 28.07.2025
 *      Author: Olly
 */

#include "AlienBullet.h"
#include "../properties/PropAnimatedSprite.h"
#include "../properties/PropMoveable.h"
#include <SFML/System/Vector2.hpp>
#include "../Constants.hpp"
#include "../../assets/AssetMappings.h"

AlienBullet::AlienBullet(const int x, const int y) :
	PropMoveable(constants::ALIEN_BULLET_SPEED, VerticalDirection::DOWN),
	PropAnimatedSprite(
		ASSETS_SPRITE_ALIEN_BULLET, 
		constants::ANIMATION_ALIEN_BULLET_LENGTH,
		 true, true
	) {
	setPosition(sf::Vector2f(x,y));
}

AlienBullet::~AlienBullet() {}



void AlienBullet::update(float timePassed) {
	updateSprite(timePassed);
	updatePosition(timePassed);
}

// # region Getters/Setters

void AlienBullet::setPosition(const sf::Vector2f pos){ sprite.setPosition(pos); }
const sf::Vector2f AlienBullet::getPosition() const { return sprite.getPosition(); };

// #endregion