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
#include "../model/Constants.hpp"
#include "AlienBulletControl.h"

AlienControl::AlienControl(Layer &layer) : layer(layer) {}

void AlienControl::populate(AlienBulletControl* alientBulletControl, LevelControl* levelControl) {
	this->alientBulletControl = alientBulletControl;
	this->levelControl = levelControl;
}

void AlienControl::update(float time_passed) {
	
	// Flag to check if any alien has reached the border
	bool anyReachedSideFlag = false;
	
	// Updates aliens, checks for dead ones and randomly spawns bullets
	for (auto it = aliens.begin(); it != aliens.end(); ) {
		// Remove alien if its dead
		if(it->getLifes() <= 0) {
			it = aliens.erase(it);
			continue;
		}
	
		// Update the alien and maybe spawn a bullet	
		it->update(time_passed);
		randomSpawnBullet(*it);		
		
		// Sets a flag if the alien has reached the borders
		if(it->getPosition().x == 0 || it->getPosition().x == constants::GAME_HEIGHT)
			anyReachedSideFlag = true;
		
		++it;
	
	}
	
	// Flag to check if any alien has reached the bottom
	bool reachedBottomFlag = false;
	
	// If any alien has reached the side, change the direction of all of them
	// Alle Aliens umdrehen wenn eins den Rand berührt und Aliens nach unten schieben
	if (anyReachedSideFlag) {
		for (auto it = aliens.begin(); it != aliens.end(); it++)
		{
			it->changeDirection();
			
			// Moves the aliens a line lower
			auto pos = it->getPosition();
			pos.y += constants::ALIEN_Y_ADVANCE;
			it->setPosition(pos);
			
			if (it->getPosition().y > constants::GAME_HEIGHT)
				reachedBottomFlag = true;
		}
	}
	
	if(reachedBottomFlag){
		// TODO: Gameover logic
	}
}

void AlienControl::draw(){
	for (auto alien_it = aliens.begin(); alien_it != aliens.end(); alien_it++) {
		layer.add_to_layer(alien_it->getSprite());
		
		if (alien_it->hasShield())
			layer.add_to_layer(alien_it->getShieldSprite());
	}
}

void AlienControl::spawnAlien(const int x, const int y, const int lifes) {
	aliens.emplace_back(x, y, lifes);
}

void AlienControl::randomSpawnBullet(Alien& alien) {
    const float random_value = (float)(rand()) / (float)(RAND_MAX);

	if (random_value < constants::ALIEN_SHOOT_CHANCE) {
		alientBulletControl->spawnBulletAt(
			alien.getPosition().x,
			alien.getPosition().y+6
		);
	}
}

// # region Getters/Setters

std::list<Alien>& AlienControl::getAliens(){ return aliens; };

// # endregion