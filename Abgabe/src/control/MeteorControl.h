/*
 * MeteorController.h
 *
 *  Created on: 27.07.2025
 *      Author: Alica
 */

#ifndef SRC_CONTROL_METEORCONTROL_H_
#define SRC_CONTROL_METEORCONTROL_H_

#include <SFML/Graphics.hpp>
#include <list>
#include "../view/Layer.hpp"
#include "../model/Meteor.h"
#include "ParticleControl.h"
#include "properties/PropDrawable.h"

class PlayerControl;

class MeteorControl : public PropDrawable {
public:
	MeteorControl(Layer &layer);
	virtual ~MeteorControl() {};
	
	// Part of setup
	// Its imperative to call this before anything else in this class
	void populate(PlayerControl* playerControl, ParticleControl* particleControl);
	
	// Event: When the game objects shall update
	void update(const float time_passed);
		
	// Spawns a new Meteor at the given position
	void spawnMeteorAt(const int x, const int y);

	virtual void draw() override;

	// Getters/Setters
	const std::list<Meteor>& getMeteors() const;

protected:
	// Communication with other control's
	PlayerControl* playerControl;
	ParticleControl* particleControl;

	// List of shot Meteors
	std::list<Meteor> meteors;
	
    // timer counts how much time has passed since last meteor spawned
    float timer;

    // time that passes, until next meteor spawns
    // TODO?: make random?
    float time_between_meteors;
};

#endif /* SRC_CONTROL_MeteorCONTROL_H_ */
