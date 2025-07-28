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
#include "Game.hpp"

AlienControl::AlienControl(Layer &layer) : layer(layer) {}
AlienControl::~AlienControl() {}

void AlienControl::update(float time_passed) {
	
	// Updates aliens, checks for dead ones and randomly spawns bullets
	for (auto it = aliens.begin(); it != aliens.end(); ) {
		it->update(time_passed);
		randomSpawnBullet(*it);		
		
		if(it->getLifes() <= 0)
			it = aliens.erase(it);
		else
			++it;
	}
}

void AlienControl::draw(){
	for (auto alien_it = aliens.begin(); alien_it != aliens.end(); alien_it++) {
		layer.add_to_layer(alien_it->getSprite());
		
		if (alien_it->getLifes() > 1)
			layer.add_to_layer(alien_it->getShieldSprite());
	}
}

void AlienControl::spawnAlien(const int x, const int y, const int lifes) {
	aliens.emplace_back(x, y, lifes);
}

void AlienControl::randomSpawnBullet(Alien& alien) {
    const float random_value = (float)(rand()) / (float)(RAND_MAX);

	if (random_value < constants::ALIEN_SHOOT_CHANCE) {
		Game::getInstance().getAlienBulletControl().spawnBulletAt(
			alien.getPosition().x,
			alien.getPosition().y+6
		);
	}
}

// # region Getters/Setters

std::list<Alien>& AlienControl::getAliens(){ return aliens; };

// # endregion