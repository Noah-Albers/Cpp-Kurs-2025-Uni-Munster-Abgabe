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

class MeteorControl {
public:

    //timer counts how much time has passed since last meteor spawned
    float timer = 0;

    //time that passes, until next meteor spawns
    // TODO?: make random?
    float time_between_meteors = 10;

	MeteorControl(Layer &layer);
	virtual ~MeteorControl();
	
	// Event: When the game objects shall update
	void update(float time_passed);
	
	// Event: When the objects are drawn to the screen
	void draw();
	
	// Spawns a new Meteor at the given position
	void spawnMeteorAt(const int x, const int y);
	
    
	
protected:
	// Layer to render the Meteors onto
	Layer &layer;

	// List of shot Meteors
	std::list<Meteor> meteors;
};

#endif /* SRC_CONTROL_MeteorCONTROL_H_ */
