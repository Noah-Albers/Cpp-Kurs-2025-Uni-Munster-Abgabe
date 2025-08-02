/*
 * PropMoveable.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#include "PropMoveable.h"

#include "../Constants.hpp"

PropMoveable::PropMoveable(
	const float speed,
	const VerticalDirection v_dir,
	const HorizontalDirection h_dir
) : hDir(h_dir), vDir(v_dir){
	setSpeed(speed);
}
PropMoveable::~PropMoveable() {}

void PropMoveable::updatePosition(const float timePassed){
	int by_x=0, by_y=0;
	if(vDir != VerticalDirection::NONE)
		by_y = vDir == VerticalDirection::DOWN ? 1 : -1;
	if(hDir != HorizontalDirection::NONE)
		by_x = hDir == HorizontalDirection::RIGHT ? 1 : -1;
	
	if(by_x != 0 || by_y != 0)
		moveBy(
			(float)by_x * this->speed * timePassed * 100.0,
			(float)by_y * this->speed * timePassed * 100.0
		);
}

void PropMoveable::moveBy(int x, int y){
	setPosition(getPosition() + sf::Vector2f(x,y));
}

void PropMoveable::setSpeed(const float _speed) {
	speed = _speed < 0 ? 0 : _speed;
}

// #region Getters and setters
	
void PropMoveable::setVerticalDirection(const VerticalDirection dir) { vDir = dir; }
void PropMoveable::setHorizontalDirection(const HorizontalDirection dir) { hDir = dir; }
const float PropMoveable::getSpeed() const { return speed; };
const VerticalDirection PropMoveable::getVerticalDirection() const { return vDir; };
const HorizontalDirection PropMoveable::getHorizontalDirection() const { return hDir; };

// #endregion


