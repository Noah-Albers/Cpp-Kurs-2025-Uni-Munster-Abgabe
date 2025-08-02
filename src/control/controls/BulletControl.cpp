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
#include <cmath>
#include <iostream>

BulletControl::BulletControl(Layer &layer) :
	PropDrawable(layer) {}
BulletControl::~BulletControl() {}

void BulletControl::populate(AlienControl* alienControl, MeteorControl* meteorControl) {
	this->alienControl = alienControl;
	this->meteorControl = meteorControl;
}

void BulletControl::update(const float timePassed) {
	// List of all aliens
	auto &aliens = alienControl->getAliens();
	auto &meteors = meteorControl->getMeteors();

	// Updates bullets, checks collisions and if they are out of scope
	for (auto it = bullets.begin(); it != bullets.end();) {
  		it->update(timePassed);
  		
		// Flag to check if the bullet shall be deleted
		// Checks if the lower end of the bullet is above the scoreboard-area
		bool deleteFlag = it->getPosition().y < -it->getSprite().getLocalBounds().size.y - constants::SCOREBOARD_HEIGHT;

		// Checks for alien collisions
		for (auto alienIt = aliens.begin(); alienIt != aliens.end();alienIt++)
			if (it->isCollidingWith(*alienIt)) {
				deleteFlag = true;
				alienIt->removeLife();
				// Ensure one bullet can at max kill one alien
				break;
			}
		

		// Checks for meteor collisions
		if(!deleteFlag)
			for (auto meteorIt = meteors.begin(); meteorIt != meteors.end();meteorIt++)
				if (it->isCollidingWith(*meteorIt))
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