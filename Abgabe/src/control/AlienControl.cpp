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

		for (auto& bullet : bullet_control->getBullets()) {
    		sf::FloatRect bulletBounds = bullet.getSprite().getGlobalBounds();
    		sf::FloatRect alienBounds = alien_it->getSprite().getGlobalBounds();

    		if (rectsIntersect(bulletBounds, alienBounds)) {
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

void AlienControl::setBulletControl(BulletControl* bullet_control) {
    this->bullet_control = bullet_control;
}


void AlienControl::spawnAlien(const int x, const int y) {
	aliens.emplace_back(x, y);
}


bool AlienControl::rectsIntersect(const sf::FloatRect& a, const sf::FloatRect& b) {
    return !(a.position.x + a.size.x < b.position.x ||
             b.position.x + b.size.x < a.position.x ||
             a.position.y + a.size.y < b.position.y ||
             b.position.y + b.size.y < a.position.y);
}
