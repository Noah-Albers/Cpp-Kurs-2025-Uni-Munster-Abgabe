/*
 * AlienControl.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Olly
 */

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics.hpp>
#include "AlienControl.h"
#include "Game.hpp"


AlienControl::AlienControl(Layer &layer) : layer(layer) {}
AlienControl::~AlienControl() {}

void AlienControl::update() {
	for (auto alien_it = aliens.begin(); alien_it != aliens.end(); ) {
		bool erased = false;

		for (auto bullet_it = bullets.begin(); bullet_it != bullets.end(); ++bullet_it) {
			sf::FloatRect bulletBounds = bullet_it->getSprite().getGlobalBounds();
			sf::FloatRect alienBounds = alien_it->getSprite().getGlobalBounds();

			if (rectsIntersect(bulletBounds, alienBounds)) {
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
	for (auto alien_it = aliens.begin(); alien_it != aliens.end(); alien_it++){
		layer.add_to_layer(alien_it->getSprite());
	}
}

void AlienControl::setBulletList(std::list<Bullet> bullets) {
	this->bullets = bullets;
}

void AlienControl::spawnAlien(const int x, const int y) {
	aliens.emplace_back(x, y);
}


bool rectsIntersect(const sf::FloatRect& a, const sf::FloatRect& b) {
    return !(a.position.x + a.size.x < b.position.x ||
             b.position.x + b.size.x < a.position.x ||
             a.position.y + a.size.y < b.position.y ||
             b.position.y + b.size.y < a.position.y);
}

