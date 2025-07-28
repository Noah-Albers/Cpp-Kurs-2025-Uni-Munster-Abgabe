/*
 * MeteorController.cpp
 *
 *  Created on: 27.07.2025
 *      Author: Alica
 */
#include "MeteorControl.h"
#include "../model/Constants.hpp"
#include "Game.hpp"
#include <cstdlib>

MeteorControl::MeteorControl(Layer &layer) :
	layer(layer) {}
MeteorControl::~MeteorControl() {}

void MeteorControl::update(float time_passed) {

	for (auto meteors_it = meteors.begin(); meteors_it != meteors.end();) {
		bool erased = false;

		// for every meteor, check whether it collides with the player and erase
		// it
		auto &player = Game::getInstance().getPlayerControl().getPlayer();

		if (meteors_it->isCollidingWith(player)) {
			Game::getInstance().getPlayerControl().damage();
			meteors_it = meteors.erase(meteors_it);
			erased = true;

			break;
		}

		//  removes any that went out of screen
		if (meteors_it->getPosition().y > constants::GAME_HEIGHT + 20) {
			meteors_it = meteors.erase(meteors_it);
			erased = true;

			break;
		}

		// Moves Meteors forward
		if (!erased) {
			meteors_it->updatePosition();
			++meteors_it;
		}
	}

	// count the time that passed since last Meteor spawn
	timer += time_passed;

	// when wanted time passed, spawn new meteor at random x coordinate and
	// reset time
	if (timer > time_between_meteors) {
		spawnMeteorAt(rand() % constants::GAME_WIDTH, -20);
		timer = 0;
	}
}

void MeteorControl::draw() {
	for (auto it = meteors.begin(); it != meteors.end(); it++)
		layer.add_to_layer(it->getSprite());
}

void MeteorControl::spawnMeteorAt(const int x, const int y) {
	meteors.emplace_back(x, y);
}
