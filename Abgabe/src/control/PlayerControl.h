/*
 * PlayerControl.h
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#ifndef SRC_CONTROL_PLAYERCONTROL_H_
#define SRC_CONTROL_PLAYERCONTROL_H_

#include <SFML/Graphics.hpp>
#include "../view/Layer.hpp"
#include "../model/Player.h"

class PlayerControl {
public:
	PlayerControl(Layer &layer);
	virtual ~PlayerControl();
	
	// Event: When the player is drawn
	void draw();
	
	// Event: When the game objects shall update
	void update();
	
	/**
	 * Event: When a key is pressed or released.
	 * @param is_now_pressed - stores if the given key got pressed (true) or released (false)
	 * @param keyCode - stores the given keycode. use sf::Keyboard::Key::<CODE> to check which key was pressed
	 */
	void keyStateChanged(bool is_now_pressed, sf::Keyboard::Key keyCode);
	
protected:
	// Layer to render the player onto
	Layer &layer;
	
	// Player object
	Player player;
};

#endif /* SRC_CONTROL_PLAYERCONTROL_H_ */
