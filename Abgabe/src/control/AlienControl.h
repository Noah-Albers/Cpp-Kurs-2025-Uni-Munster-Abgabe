/*
 * AlienControl.h
 *
 *  Created on: 26.07.2025
 *      Author: Olly
 */

#ifndef SRC_CONTROL_ALIENCONTROL_H_
#define SRC_CONTROL_ALIENCONTROL_H_

#include <SFML/Graphics.hpp>
#include "../view/Layer.hpp"
#include "../model/Alien.h"
#include "AlienBulletControl.h"
#include "LevelControl.h"
#include "properties/PropDrawable.h"
#include <list>

// Declares classes to avoid circular dependencies
class AlienBulletControl;

class AlienControl : public PropDrawable {
public:
	AlienControl(Layer &layer);
	
	// Part of setup
	// Its imperative to call this before anything else in this class
	void populate(AlienBulletControl* alientBulletControl, LevelControl* levelControl);
	
	// Event: When the alien is drawn
	virtual void draw() override;
	
	// Event: When the game objects shall update
	void update(float time_passed);

	void spawnAlien(const int x, const int y, const int lifes);
	
	// Getters/Setters
	std::list<Alien>& getAliens();
	
protected:
	// Communication with other control's
	AlienBulletControl* alientBulletControl;
	LevelControl* levelControl;
	
	// All Alien objects
	std::list<Alien> aliens;
	
	// General motion that should be applied to all aliens
	// and steadily decrease.
	// Used for animations
	float downwardMotion;
	
	// Randomly spawns a bullet at the alien
	void randomSpawnBullet(const Alien& alien);

	// Checks if all aliens are inside the actual game field or still
	// outside (Used to slowly transition them)
	const bool areAliensInGamefield() const;
	
};

#endif /* SRC_CONTROL_ALIENCONTROL_H_ */
