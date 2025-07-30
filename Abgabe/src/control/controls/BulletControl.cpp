/*
 * BulletController.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#include "BulletControl.h"
#include "../properties/PropDrawable.h"
#include "../../model/Constants.hpp"
#include "MeteorControl.h"
#include "AlienControl.h"

BulletControl::BulletControl(Layer &layer) :
	PropDrawable(layer) {}
BulletControl::~BulletControl() {}

void BulletControl::populate(AlienControl* alienControl, MeteorControl* meteorControl) {
	this->alienControl = alienControl;
	this->meteorControl = meteorControl;
}

void BulletControl::update(const float time_passed) {
	// List of all aliens
	auto &aliens = alienControl->getAliens();
	auto &meteors = meteorControl->getMeteors();

	// Updates bullets, checks collisions and if they are out of scope
	for (auto it = bullets.begin(); it != bullets.end();) {
		it->update(time_passed);

		// Flag to check if the bullet shall be deleted
		// Checks if the lower end of the bullet is above the scoreboard-area
		bool deleteFlag = it->getPosition().y < -it->getSprite().getLocalBounds().size.y - constants::SCOREBOARD_HEIGHT;

		// Checks for alien collisions
		for (auto alien_it = aliens.begin(); alien_it != aliens.end();alien_it++)
			if (it->isCollidingWith(*alien_it)) {
				deleteFlag = true;
				alien_it->removeLife();
			}

		// Checks for meteor collisions
		for (auto meteor_it = meteors.begin(); meteor_it != meteors.end();meteor_it++)
			if (it->isCollidingWith(*meteor_it))
				deleteFlag = true;

		if (deleteFlag)
			it = bullets.erase(it);
		else
			++it;
	}
}

void BulletControl::draw() {
	for (auto it = bullets.begin(); it != bullets.end(); it++)
		layer.add_to_layer(it->getSprite());
}

void BulletControl::spawnBulletAt(const int x, const int y) {
	bullets.emplace_back(x, y);
}

// #region Getters/Setters

const std::list<Bullet> &BulletControl::getBullets() const { return bullets; }

// #endregion