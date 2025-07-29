/*
 * Scoreboard.h
 *
 *  Created on: 29.07.2025
 *      Author: Noah
 */

#ifndef SRC_MODEL_SCOREBOARD_H_
#define SRC_MODEL_SCOREBOARD_H_

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
class Scoreboard {
public:
	/**
	 * @param space - how much space shall be left to the side and top
	 */
	Scoreboard(float space);

	// Renders the scoreboard onto the window
	void draw(sf::RenderWindow& win);

	// Shows the given score as text on the scoreboard
	void displayScore(int score);
	
	// Getters/Setters
	// Returns the y-coordinate of the scoreboard-text sprite at the bottom
	int getBottomYCoordinate();

protected:
	sf::Font font;
	
	sf::Text scoreboardLabel;
	sf::Text scoreLabel;
};

#endif /* SRC_MODEL_SCOREBOARD_H_ */
