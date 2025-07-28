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

Meteor::Meteor(const int x, const int y) :
	PropMoveable(5, VerticalDirection::DOWN),
	PropSprite("assets/sprites/Asteroid.png", 64, 64)
{
	sprite.setPosition(sf::Vector2f(x,y));
}

Meteor::~Meteor() {}

sf::Vector2f Meteor::getPosition() {
	return sprite.getPosition();
}

void Meteor::setPosition(sf::Vector2f pos){
	sprite.setPosition(pos);
}
