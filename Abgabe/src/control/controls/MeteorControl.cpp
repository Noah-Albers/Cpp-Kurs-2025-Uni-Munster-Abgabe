/*
 * MeteorController.cpp
 *
 *  Created on: 27.07.2025
 *      Author: Alica
 */
#include "MeteorControl.h"
#include "ParticleControl.h"
#include "../../model/Constants.hpp"
#include "PlayerControl.h"
#include "../properties/PropDrawable.h"
#include <cstdlib>
#include <list>

MeteorControl::MeteorControl(Layer &layer) :
	PropDrawable(layer),
	timer(0)
	{}

void MeteorControl::populate(PlayerControl* playerControl, ParticleControl* particleControl) {
	this->playerControl = playerControl;
	this->particleControl = particleControl;
}

void MeteorControl::update(const float time_passed) {
	// Updates meteors, checks collision and if they are out of scope
	for (auto it = meteors.begin(); it != meteors.end();) {
		it->updatePosition(time_passed);

		// Checks if the meteor is out of scope or has collided with the player
		bool hasCollided = (
			   !playerControl->getPlayer().isDead()
			&& it->isCollidingWith(playerControl->getPlayer())
		);
		bool isOutOfScope = it->getPosition().y > constants::GAME_HEIGHT + 20;

		if (hasCollided){
			playerControl->damagePlayer();
			particleControl->spawnMeteorExplosionParticle(it->getPosition().x,it->getPosition().y);
		}

		// Removes the bullet if out of scope or collided with playerd
		if (hasCollided || isOutOfScope)
			it = meteors.erase(it);
		else
			++it;
	}

	// count the time that passed since last Meteor spawn
	timer += time_passed;

	// when wanted time passed, spawn new meteor at random x coordinate and
	// reset time
	if (timer > constants::METEOR_DELAY) {
		spawnMeteorAt(rand() % constants::GAME_WIDTH, -constants::SCOREBOARD_HEIGHT);
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

// #region Getters/Setters

const std::list<Meteor>& MeteorControl::getMeteors() const { return meteors; }

// #endregion
