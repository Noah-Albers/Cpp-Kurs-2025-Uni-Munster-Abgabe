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
#include "Constants.hpp"

AlienBullet::AlienBullet(const int x, const int y) :
	PropMoveable(constants::ALIEN_BULLET_SPEED, VerticalDirection::DOWN),
	PropSprite("assets/sprites/Alien_Bullet.png", 18, 38, 0.5)
{
	sprite.setPosition(sf::Vector2f(x,y));
    animation_clock.restart();
    frame_index = 0;
}

AlienBullet::~AlienBullet() {}

sf::Vector2f AlienBullet::getPosition() {
	return sprite.getPosition();
}

void AlienBullet::setPosition(sf::Vector2f pos){
	sprite.setPosition(pos);
}

void AlienBullet::nextSprite() {
    if (animation_clock.getElapsedTime().asSeconds() > 0.1) {
        frame_index++;
        this->setFrame(frame_index);
        animation_clock.restart();
    }
}
