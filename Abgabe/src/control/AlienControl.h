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

class AlienControl {
public:
	AlienControl(Layer &layer);
	virtual ~AlienControl();
	
	// Event: When the player is drawn
	void draw();
	
	// Event: When the game objects shall update
	void update();
	
protected:
	// Layer to render the player onto
	Layer &layer;
	
	// Player object
	Alien alien;
};

#endif /* SRC_CONTROL_PLAYERCONTROL_H_ */
