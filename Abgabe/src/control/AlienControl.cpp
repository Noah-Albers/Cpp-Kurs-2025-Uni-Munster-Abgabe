/*
 * AlienControl.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Olly
 */

#include "AlienControl.h"
#include "Game.hpp"

AlienControl::AlienControl(Layer &layer) : layer(layer) {}
AlienControl::~AlienControl() {}

void AlienControl::update(){
	this->alien.update();
}

void AlienControl::draw(){
	this->layer.add_to_layer(this->alien.getSprite());
}