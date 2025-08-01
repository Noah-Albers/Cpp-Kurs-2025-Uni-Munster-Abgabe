/*
 * AlienControl.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Olly
 */

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <list>
#include "AlienControl.h"
#include "../../model/Constants.hpp"
#include "AlienBulletControl.h"
#include "PlayerControl.h"
#include "../properties/PropDrawable.h"

AlienControl::AlienControl(Layer &layer) :
	PropDrawable(layer),
	downwardMotion(0) {};

AlienControl::~AlienControl() {};

void AlienControl::populate(
	AlienBulletControl* alientBulletControl, LevelControl* levelControl,
	PlayerControl* playerControl
	) {
	this->alientBulletControl = alientBulletControl;
	this->levelControl = levelControl;
	this->playerControl = playerControl;
	
}

void AlienControl::update(float timePassed) {
	
	// If not all aliens are inside the game field, transition them there
	if(!areAliensInGamefield()){
		for(auto it = aliens.begin(); it != aliens.end();) {
			it->moveBy(0, constants::ALIEN_SPAWN_SPEED);
			
			if(it->getLifes() <= 0){
				it = aliens.erase(it);
				levelControl->increaseScore();
			}
			else ++it;
		}
		return;
	}
	
	// Flags to check if any alien has reached the border or the bottom
	bool anyReachedSideFlag = false;
	bool reachedBottomFlag = false;
	
	// Updates aliens, checks for dead ones and randomly spawns bullets
	for (auto it = aliens.begin(); it != aliens.end(); ) {
		// Remove alien if its dead
		if(it->getLifes() <= 0) {
			it = aliens.erase(it);
			levelControl->increaseScore();
			continue;
		}
	
		// Update the alien and maybe spawn a bullet	
		it->update(timePassed);
		randomSpawnBullet(*it);		
		
		// Sets a flag if the alien has reached the borders
		if(it->getPosition().x == 0 || it->getPosition().x == constants::GAME_HEIGHT)
			anyReachedSideFlag = true;
		
		// If there is downwards motion, apply it
		if(downwardMotion > 0)
			it->moveBy(0, 1);
		
		if(it->getPosition().y >= constants::GAME_HEIGHT)
			reachedBottomFlag = true;
		
		++it;
	}
	
	// Steadily decreases the downwards motion
	if(downwardMotion > 0)
		--downwardMotion;
	
	// If any alien has reached the side, start moving them down
	// and change their direction
	if(anyReachedSideFlag){
		for(auto it = aliens.begin(); it != aliens.end(); it++)
			it->changeDirection();
		
		// Only apply downward motion if the player is not dead.
		// This prevents them from walking of-screen when the player has lost
		if(!playerControl->getPlayer().isDead())
			downwardMotion = constants::ALIEN_ADVANCE_SPEED;
	}
	
	// When the aliens reach the bottom, this kills the player
	// to represent a game-over
	if(reachedBottomFlag)
		playerControl->killPlayer();
}

void AlienControl::draw(){
	for (auto it = aliens.begin(); it != aliens.end(); it++) {
		layer.add_to_layer(it->getSprite());
		
		if (it->hasShield())
			layer.add_to_layer(it->getShieldSprite());
	}
}

void AlienControl::spawnAlienAt(const int x, const int y, const int lifes, const float speed) {
	aliens.emplace_back(x, y, lifes, speed);
}

void AlienControl::randomSpawnBullet(const Alien& alien) {
	// Prevents more than a configureable amount of alien bullets to be spawned
	if(alientBulletControl->getBullets().size() >= constants::MAX_ALIEN_BULLETS) return;
	// Prevents aliens from shooting if the player is dead
	if(playerControl->getPlayer().isDead()) return;
	
    const float rdmValue = (float)(rand()) / (float)(RAND_MAX);

	if (rdmValue < constants::ALIEN_SHOOT_CHANCE) {
		alientBulletControl->spawnBulletAt(
			alien.getPosition().x,
			alien.getPosition().y
		);
	}
}

const bool AlienControl::areAliensInGamefield() const {
	// Checks if each alien is inside the game field
	for(auto it = aliens.begin(); it != aliens.end(); it++)
		if(it->getPosition().y < 0)
			return false;
	return true;
}

// # region Getters/Setters

std::list<Alien>& AlienControl::getAliens() { return aliens; };

// # endregion