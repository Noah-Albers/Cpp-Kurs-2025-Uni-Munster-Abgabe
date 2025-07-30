/*
 * AlienBulletControl.cpp
 *
 *  Created on: 28.07.2025
 *      Author: Olly
 */

#include "AlienBulletControl.h"
#include "PlayerControl.h"
#include "properties/PropDrawable.h"
#include "../model/Constants.hpp"
#include "PlayerControl.h"

AlienBulletControl::AlienBulletControl(Layer &layer) : PropDrawable(layer) {}

void AlienBulletControl::populate(PlayerControl* playerControl) {
	this->playerControl = playerControl;
}

void AlienBulletControl::update(const float time_passed){
	// Updates bullets, removes any out of bounds and handles player collision
	for(auto it = alien_bullets.begin(); it != alien_bullets.end();){
		it->update(time_passed);
		
		// Checks if the bullet is out of scope or has collided with the player
		bool hasCollided = it->isCollidingWith(playerControl->getPlayer());
		bool isOutOfScope = it->getPosition().y > constants::GAME_HEIGHT + 20;
		
		if(hasCollided)
			playerControl->damagePlayer();
		
		// Removes the bullet if out of scope or collided with playerd
		if(hasCollided || isOutOfScope)
			it = alien_bullets.erase(it);
		else
			++ it;
	}	
}

void AlienBulletControl::draw(){
	for(auto it = alien_bullets.begin(); it != alien_bullets.end(); it++)
		layer.add_to_layer(it->getSprite());
}

void AlienBulletControl::spawnBulletAt(const int x, const int y) {
	alien_bullets.emplace_back(x,y);
}

// #region Getters/Setters

const std::list<AlienBullet>& AlienBulletControl::getBullets() const { return alien_bullets; };

// #endregion