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

void AlienControl::update() {
	for (auto alien_it = aliens.begin(); alien_it != aliens.end(); ) {
		bool erased = false;

		for (auto bullet_it = bullets.begin(); bullet_it != bullets.end(); ++bullet_it) {
			sf::Vector2f bullet_pos = bullet_it->getPosition();

			if (bullet_pos == alien_it->getPosition()) {
				alien_it = aliens.erase(alien_it);
				erased = true;
				break;  // Stop checking bullets for this alien
			}
		}

		if (!erased) {
			alien_it->update();
			++alien_it;
		}
	}
}

void AlienControl::draw(){
	for (auto bullet_it = aliens.begin(); bullet_it != aliens.end(); bullet_it++){
		layer.add_to_layer(bullet_it->getSprite());
	}
}

void AlienControl::setBulletList(std::list<Bullet> bullets) {
	this->bullets = bullets;
}

void AlienControl::spawnAlien(const int x, const int y) {
	aliens.emplace_back(x, y);
}