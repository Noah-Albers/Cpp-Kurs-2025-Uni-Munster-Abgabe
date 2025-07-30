/*
 * BulletController.h
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#ifndef SRC_CONTROL_BULLETCONTROL_H_
#define SRC_CONTROL_BULLETCONTROL_H_

#include <SFML/Graphics.hpp>
#include <list>
#include "../view/Layer.hpp"
#include "../model/Bullet.h"
#include "./properties/PropDrawable.h"

// Declares classes to avoid circular dependencies
class MeteorControl;
class AlienControl;

class BulletControl : public PropDrawable {
public:
	BulletControl(Layer &layer);
	
	// Part of setup
	// Its imperative to call this before anything else in this class
	void populate(AlienControl* alienControl, MeteorControl* meteorControl);
	
	// Event: When the game objects shall update
	void update(const float time_passed);
	
	// Spawns a new bullet at the given position
	void spawnBulletAt(const int x, const int y);

	virtual void draw() override;

	// Getters/Setters
	const std::list<Bullet>& getBullets() const;
	
protected:
	// Communication with other control's
	AlienControl* alienControl;
	MeteorControl* meteorControl;
	
	// List of shot bullets
	std::list<Bullet> bullets;
};

#endif /* SRC_CONTROL_BULLETCONTROL_H_ */
