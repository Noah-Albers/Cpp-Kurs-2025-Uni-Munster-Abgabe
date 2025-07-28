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

class UIControl {
public:
	UIControl(sf::RenderWindow& win);
	
	// Draws the ui on the screen
	void draw();
	
	// Advances the background
	void nextBackground();
	
	// Sets a new score and updates the screen
	void setScore(int score);
	
	// Updates the object
	void update(float time_passed);
	
protected:
	// Score the player achieved
	// TODO: Maybe move this somewhere else
	int score;

	// Window to render the ui onto
	sf::RenderWindow& win;
	
	// Text's for the score
	sf::Text scoreboardLabel, scoreLabel;
	
	// Healthbar object
	Healthbar healthbar;
	
	// Background object
	Background background;
};

#endif /* SRC_CONTROL_UICONTROL_H_ */
