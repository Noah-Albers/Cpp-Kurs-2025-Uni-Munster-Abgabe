/*
 * AlienBulletControl.cpp
 *
 *  Created on: 28.07.2025
 *      Author: Olly
 */

#include "AlienBulletControl.h"
#include "properties/PropDrawable.h"
#include "../model/Constants.hpp"

AlienBulletControl::AlienBulletControl(Layer &layer) : PropDrawable(layer) {}
AlienBulletControl::~AlienBulletControl() {}

void AlienBulletControl::update(){
	// Moves bullets forward and removes any that went out of screen
	for(auto it = alien_bullets.begin(); it != alien_bullets.end();){
		it->updatePosition();
		
		if(it->getPosition().y > constants::GAME_HEIGHT + 20)
			it = alien_bullets.erase(it);
		else
            it->nextSprite();
			++it;
	}	
}

void AlienBulletControl::draw(){
	for(auto it = alien_bullets.begin(); it != alien_bullets.end(); it++)
		layer.add_to_layer(it->getSprite());
}

void AlienBulletControl::spawnBulletAt(const int x, const int y) {
	alien_bullets.emplace_back(x,y);
}

std::list<AlienBullet>& AlienBulletControl::getBullets() {
	return alien_bullets;
}