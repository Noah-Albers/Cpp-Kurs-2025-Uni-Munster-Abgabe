/*
 * AlienBulletControl.cpp
 *
 *  Created on: 28.07.2025
 *      Author: Olly
 */

#include "AlienBulletControl.h"
#include "PlayerControl.h"
#include "../properties/PropDrawable.h"
#include "../../model/Constants.hpp"
#include "PlayerControl.h"

AlienBulletControl::AlienBulletControl(Layer &layer) :
	PropDrawable(layer) {}

AlienBulletControl::~AlienBulletControl() {}

void AlienBulletControl::populate(PlayerControl* playerControl) {
	this->playerControl = playerControl;
}

void AlienBulletControl::update(const float timePassed){
	// Updates bullets, removes any out of bounds and handles player collision
	for(auto it = alienBullets.begin(); it != alienBullets.end();){
		it->update(timePassed);
		
		// Checks if the bullet is out of scope or has collided with the player
		bool hasCollided = (
			   !playerControl->getPlayer().isDead()
			&& it->isCollidingWith(playerControl->getPlayer())
		);
		bool isOutOfScope = it->getPosition().y > constants::GAME_HEIGHT + it->getSprite().getLocalBounds().size.y;
		
		if(hasCollided)
			playerControl->damagePlayer();
		
		// Removes the bullet if out of scope or collided with player
		if(hasCollided || isOutOfScope)
			it = alienBullets.erase(it);
		else
			++ it;
	}	
}

void AlienBulletControl::draw(){
	for(auto it = alienBullets.begin(); it != alienBullets.end(); it++)
		layer.add_to_layer(it->getSprite());
}

void AlienBulletControl::spawnBulletAt(const int x, const int y) {
	alienBullets.emplace_back(x,y);
}

// #region Getters/Setters

const std::list<AlienBullet>& AlienBulletControl::getBullets() const { return alienBullets; };

// #endregion