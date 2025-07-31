/*
 * AlienShield.cpp
 *
 *  Created on: 30.07.2025
 *      Author: Noah
 */

#include "AlienShield.h"
#include "../../assets/AssetMappings.h"
#include <SFML/System/Vector2.hpp>
#include "../Constants.hpp"

AlienShield::AlienShield() :
	PropAnimatedSprite(
		ASSETS_SPRITE_ALIEN_SHIELD, 
		constants::ANIMATION_ALIEN_SHIELD_LENGTH,
		true, true
	) {}

void AlienShield::setPosition(const sf::Vector2f pos){
	sprite.setPosition(pos);
}

