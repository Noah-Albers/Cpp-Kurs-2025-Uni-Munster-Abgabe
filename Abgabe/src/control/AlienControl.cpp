/*
 * AlienControl.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Olly
 */

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "AlienControl.h"
#include "../model/Constants.hpp"
#include "Game.hpp"

AlienControl::AlienControl(Layer &layer) : layer(layer) {}
AlienControl::~AlienControl() {}

void AlienControl::update(float time_passed) {
	auto& bullets = Game::getInstance().getBulletControl().getBullets();
	for (auto alien_it = aliens.begin(); alien_it != aliens.end(); ) {
		bool erased = false;

		for (auto bullet_it = bullets.begin(); bullet_it != bullets.end();) {
			if(alien_it->isCollidingWith(*bullet_it)){	
				alien_it->removeLife();
				if (alien_it->getLifes() == 0) {
					alien_it = aliens.erase(alien_it);
					erased = true;
				}
				bullet_it = bullets.erase(bullet_it);
        		break;
    		}
			++bullet_it;
		}

		if (!erased) {
			alien_it->update(time_passed);
			randomSpawnBullet(*alien_it);
			++alien_it;
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
		Game::getInstance().getAlienBulletControl().spawnBulletAt(
			alien.getPosition().x,
			alien.getPosition().y+6
		);
	}
}
