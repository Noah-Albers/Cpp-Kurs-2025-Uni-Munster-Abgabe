/*
 * BulletController.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#include "BulletControl.h"
#include "properties/PropDrawable.h"

BulletControl::BulletControl(Layer &layer) : PropDrawable(layer) {}
BulletControl::~BulletControl() {}

void BulletControl::update(){
	// Moves bullets forward and removes any that went out of screen
	for(auto it = bullets.begin(); it != bullets.end();){
		it->updatePosition();
		
		if(it->getPosition().y < -20)
			it = bullets.erase(it);
		else
			++it;
	}	
}

void BulletControl::draw(){
	for(auto it = bullets.begin(); it != bullets.end(); it++)
		layer.add_to_layer(it->getSprite());
}

void BulletControl::spawnBulletAt(const int x, const int y) {
	bullets.emplace_back(x,y);
}