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
#include "../../view/Layer.hpp"
#include "../../model/game/AlienBullet.h"
#include "../properties/PropDrawable.h"

// Declares classes to avoid circular dependencies
class PlayerControl;

class AlienBulletControl : public PropDrawable {
public:
	AlienBulletControl(Layer &layer);
	virtual ~AlienBulletControl();
	
	// Part of setup
	// Its imperative to call this before anything else in this class
	void populate(PlayerControl* playerControl);
	
	// Event: When the game objects shall update
	void update(const float timePassed);
	
	// Spawns a new bullet at the given position
	virtual void spawnBulletAt(const int x, const int y);
	
	virtual void draw() override;

	// Getters/Setters
	virtual const std::list<AlienBullet>& getBullets() const;

protected:
	// Communication with other control's
	PlayerControl* playerControl;
	
	// List of shot bullets
	std::list<AlienBullet> alienBullets;
};

#endif /* SRC_CONTROL_ALIENBULLETCONTROL_H_ */
