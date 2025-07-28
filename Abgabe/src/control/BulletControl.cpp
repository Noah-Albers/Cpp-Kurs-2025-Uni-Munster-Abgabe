/*
 * BulletController.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#include "BulletControl.h"
#include "Game.hpp"
#include "properties/PropDrawable.h"

BulletControl::BulletControl(Layer &layer) :
	PropDrawable(layer) {}
BulletControl::~BulletControl() {}

void BulletControl::update(float time_passed) {
	// List of all aliens
	auto &aliens = Game::getInstance().getAlientControl().getAliens();
	auto &meteors = Game::getInstance().getMeteorControl().getMeteors();

	// Updates bullets, checks collisions and if they are out of scope
	for (auto it = bullets.begin(); it != bullets.end();) {
		it->updatePosition(time_passed);

		// Flag to check if the bullet shall be deleted
		bool deleteFlag = it->getPosition().y < -20;

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

std::list<Bullet> &BulletControl::getBullets() { return bullets; }