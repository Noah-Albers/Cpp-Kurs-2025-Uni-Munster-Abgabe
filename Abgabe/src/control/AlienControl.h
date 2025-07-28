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
#include <list>

class AlienControl {
public:
	AlienControl(Layer &layer);
	virtual ~AlienControl();
	
	// Event: When the alien is drawn
	void draw();
	
	// Event: When the game objects shall update
	void update(float time_passed);

	void spawnAlien(const int x, const int y);
	
protected:
	// Layer to render the player onto
	Layer &layer;
	
	// All Alien objects
	std::list<Alien> aliens;
};

#endif /* SRC_CONTROL_ALIENCONTROL_H_ */
