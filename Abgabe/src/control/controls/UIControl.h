/*
 * UIControl.h
 *
 *  Created on: 27.07.2025
 *      Author: Noah
 */

#ifndef SRC_CONTROL_UICONTROL_H_
#define SRC_CONTROL_UICONTROL_H_

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Window.hpp>

#include "../../model/interface/Background.h"
#include "../../model/interface/Healthbar.h"
#include "../../model/interface/Scoreboard.h"
#include "../../model/interface/Deathmessage.h"
#include "../../model/interface/Shieldbar.h"
#include "PlayerControl.h"
#include "../../view/Layer.hpp"

class UIControl {
public:
	UIControl(Layer& uiLayer, Layer& backgroundLayer);
	virtual ~UIControl();
	
	// Part of setup
	// Its imperative to call this before anything else in this class
	void populate(PlayerControl* playerControl);
	
	// Draws the ui on the screen
	void draw();
	
	// Advances the background
	void nextBackground();
	
	// Sets a new score and updates the screen
	virtual void displayScore(const int score);
	
	// Updates the object
	void update(const float time_passed);
	
protected:
	// Communication with other control's
	PlayerControl* playerControl;

	// Font used for text
	sf::Font font;

	

	// Layer to render the ui and background onto
	Layer& uiLayer;
	Layer& backgroundLayer;
	
	// Displays the score which the user has achived
	Scoreboard scoreboard;
	
	// Shows the healthbar
	Healthbar healthbar;
	
	// Shield bar
	Shieldbar shieldbar;
	
	// Renders the background
	Background background;
	
	// Displays the death message
	Deathmessage deathmessage;
	
};

#endif /* SRC_CONTROL_UICONTROL_H_ */
