/*
 * UIControl.h
 *
 *  Created on: 27.07.2025
 *      Author: Noah
 */

#ifndef SRC_CONTROL_UICONTROL_H_
#define SRC_CONTROL_UICONTROL_H_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Window.hpp>

class UIControl {
public:
	UIControl(sf::RenderWindow& win);
	
	// Draws the ui on the screen
	void draw();
	
	// Sets a new score and updates the screen
	void setScore(int score);
	
protected:
	// Score the player achieved
	// TODO: Maybe move this somewhere else
	int score;

	// Window to render the ui onto
	sf::RenderWindow& win;
	
	// Text's for the score
	sf::Text scoreboardLabel, scoreLabel;
};

#endif /* SRC_CONTROL_UICONTROL_H_ */
