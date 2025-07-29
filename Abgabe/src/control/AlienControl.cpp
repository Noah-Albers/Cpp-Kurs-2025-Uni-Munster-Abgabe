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

void AlienControl::populate(AlienBulletControl* alientBulletControl, LevelControl* levelControl){
	this->alientBulletControl = alientBulletControl;
	this->levelControl = levelControl;
}

void AlienControl::update(float time_passed) {
	bool change_direction = false;
	// Updates aliens, checks for dead ones and randomly spawns bullets
	for (auto it = aliens.begin(); it != aliens.end(); ) {
		it->update(time_passed);
		randomSpawnBullet(*it);		
		
		if(it->getLifes() <= 0) {
			it = aliens.erase(it);
			levelControl->alien_killed();
		}
		else {
			if(it->getPosition().x == 0 || it->getPosition().x == constants::GAME_HEIGHT)
				change_direction = true;
			if (it->getPosition().y > constants::GAME_HEIGHT) {
				// Game over logik here
			}
			++it;
		}
	}

	// Alle Aliens umdrehen wenn eins den Rand berührt und Aliens nach unten schieben
	if (change_direction) {
		for (auto it = aliens.begin(); it != aliens.end(); it++)
		{
			it->changeDirection();
			sf::Vector2f pos = it->getPosition();
			pos.y = pos.y + constants::ALIEN_Y_ADVANCE;
			it->setPosition(pos);
		}
		
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
		alientBulletControl->spawnBulletAt(
			alien.getPosition().x,
			alien.getPosition().y+6
		);
	}
}

// # region Getters/Setters

std::list<Alien>& AlienControl::getAliens(){ return aliens; };

// # endregion