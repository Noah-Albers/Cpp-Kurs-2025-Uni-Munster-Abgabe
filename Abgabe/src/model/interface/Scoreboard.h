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
#include "../../view/Layer.hpp"

class Scoreboard {
public:
	Scoreboard(const sf::Font& font);

	/**
	 * Must be called after the font has been loaded
	 * @param space - how much space shall be left to the side and top
	 */
	void initialize(const float space);

	// Renders the scoreboard onto the window
	void draw(Layer& win) const;

	// Shows the given score as text on the scoreboard
	void displayScore(int score);
	
	// Getters/Setters
	// Returns the y-coordinate of the scoreboard-text sprite at the bottom
	const int getBottomYCoordinate() const;

protected:
	sf::Text scoreboardLabel;
	sf::Text scoreLabel;
};

#endif /* SRC_MODEL_SCOREBOARD_H_ */
