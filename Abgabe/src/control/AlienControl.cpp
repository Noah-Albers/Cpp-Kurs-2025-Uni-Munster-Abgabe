/*
 * AlienControl.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Olly
 */

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "AlienControl.h"
#include "Game.hpp"


AlienControl::AlienControl(Layer &layer) : layer(layer) {}
AlienControl::~AlienControl() {}

void AlienControl::update() {
	for (auto alien_it = aliens.begin(); alien_it != aliens.end(); ) {
		bool erased = false;

		for (auto& bullet : Game::getInstance().getBulletControl().getBullets()) {
			auto bulletBounds = bullet.getSprite().getGlobalBounds();
			auto alientBounds = alien_it->getSprite().getGlobalBounds();

			if(bulletBounds.findIntersection(alientBounds)){
        		alien_it = aliens.erase(alien_it);
        		erased = true;
        		break;
    		}
		}


		if (!erased) {
			alien_it->update();
			++alien_it;
		}
	}
}

void AlienControl::draw(){
	for (auto alien_it = aliens.begin(); alien_it != aliens.end(); alien_it++){
		layer.add_to_layer(alien_it->getSprite());
	}
}

void AlienControl::spawnAlien(const int x, const int y) {
	aliens.emplace_back(x, y);
}
