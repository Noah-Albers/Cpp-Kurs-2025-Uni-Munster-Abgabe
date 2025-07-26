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
) : h_dir(h_dir), v_dir(v_dir), speed(speed) {}
PropMoveable::~PropMoveable() {}

void PropMoveable::updatePosition(){
	int by_x=0, by_y=0;
	if(v_dir != VerticalDirection::NONE)
		by_y = v_dir == VerticalDirection::DOWN ? 1 : -1;
	if(h_dir != HorizontalDirection::NONE)
		by_x = h_dir == HorizontalDirection::RIGHT ? 1 : -1;
	
	if(by_x != 0 || by_y != 0)
		moveBy(by_x * this->speed,by_y * this->speed);
}


void PropMoveable::moveBy(int x, int y){
	setPosition(getPosition() + sf::Vector2f(x,y));
}

// #region Getters and setters
	
void PropMoveable::setVerticalDirection(const VerticalDirection dir) { v_dir = dir; }
void PropMoveable::setHorizontalDirection(const HorizontalDirection dir) { h_dir = dir; }
void PropMoveable::setSpeed(const float _speed) { speed = _speed; }

// #endregion


