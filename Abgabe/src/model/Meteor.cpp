/*
 * Meteor.cpp
 *
 *  Created on: 27.07.2025
 *      Author: Alica
 */

#include "Meteor.h"
#include "properties/PropMoveable.h"
#include "properties/PropSprite.h"
#include <SFML/System/Vector2.hpp>

#include "../assets/AssetMappings.h"

Meteor::Meteor(const int x, const int y) :
	PropMoveable(2, VerticalDirection::DOWN),
	PropSprite(ASSETS_SPRITE_METEOR, true)
{
	// Adjusts the y position to let the user define the lower boundry
	sprite.setPosition(sf::Vector2f(x,y - sprite.getLocalBounds().size.y));
}

sf::Vector2f Meteor::getPosition() {
	return sprite.getPosition();
}

void Meteor::setPosition(sf::Vector2f pos){
	sprite.setPosition(pos);
}
