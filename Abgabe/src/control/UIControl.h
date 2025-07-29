/*
 * UIControl.h
 *
 *  Created on: 27.07.2025
 *      Author: Noah
 */

#ifndef SRC_CONTROL_UICONTROL_H_
#define SRC_CONTROL_UICONTROL_H_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Window.hpp>

#include "../model/Background.h"
#include "../model/Healthbar.h"
#include "../model/Scoreboard.h"
#include "PlayerControl.h"
#include "../view/Layer.hpp"

class UIControl {
public:
	UIControl(Layer& uiLayer, Layer& backgroundLayer);
	
	// Part of setup
	// Its imperative to call this before anything else in this class
	void populate(PlayerControl* playerControl);
	
	// Draws the ui on the screen
	void draw();
	
	// Advances the background
	void nextBackground();
	
	// Sets a new score and updates the screen
	void setScore(int score);
	
	// Updates the object
	void update(float time_passed);
	
protected:
	// Communication with other control's
	PlayerControl* playerControl;

	// Score the player achieved
	// TODO: Maybe move this somewhere else
	int score;

	// Layer to render the ui and background onto
	Layer& uiLayer;
	Layer& backgroundLayer;
	
	// Text's for the score
	Scoreboard scoreboard;
	
	// Healthbar object
	Healthbar healthbar;
	
	// Background object
	Background background;
};

#endif /* SRC_CONTROL_UICONTROL_H_ */
