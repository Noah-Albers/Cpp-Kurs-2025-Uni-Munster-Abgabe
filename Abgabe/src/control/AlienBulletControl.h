/*
 * AlienBulletControl.h
 *
 *  Created on: 28.07.2025
 *      Author: Olly
 */

#ifndef SRC_CONTROL_ALIENBULLETCONTROL_H_
#define SRC_CONTROL_ALIENBULLETCONTROL_H_

#include <SFML/Graphics.hpp>
#include <list>
#include "../view/Layer.hpp"
#include "../model/AlienBullet.h"
#include "./properties/PropDrawable.h"

class AlienBulletControl : public PropDrawable {
public:
	AlienBulletControl(Layer &layer);
	virtual ~AlienBulletControl();
	
	// Event: When the game objects shall update
	void update();
	
	// Spawns a new bullet at the given position
	void spawnBulletAt(const int x, const int y);

	// Returns the Bulletlist
	std::list<AlienBullet>& getBullets();
	
	virtual void draw() override;
	
protected:
	// List of shot bullets
	std::list<AlienBullet> alien_bullets;
};

#endif /* SRC_CONTROL_ALIENBULLETCONTROL_H_ */
