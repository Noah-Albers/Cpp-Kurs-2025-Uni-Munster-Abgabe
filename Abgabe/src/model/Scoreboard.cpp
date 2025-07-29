/*
 * Scoreboard.cpp
 *
 *  Created on: 29.07.2025
 *      Author: Noah
 */

#include "Scoreboard.h"
#include "../assets/AssetMappings.h"
#include <SFML/Graphics/RenderWindow.hpp>

Scoreboard::Scoreboard(float space) :
	scoreboardLabel(font),
	scoreLabel(font)
	{

	// Loads the font
	if (!font.openFromFile(ASSETS_FONT_DEFAULT))
        throw std::runtime_error("Failed to load Font");

	// Style options for the scoreboard
	scoreboardLabel.setString("Score: ");
    scoreboardLabel.setFillColor(sf::Color::White);
    scoreboardLabel.setStyle(sf::Text::Bold);
	scoreLabel.setFillColor(sf::Color::Red);

    // Set positions
    scoreboardLabel.setPosition({space, space});

	scoreLabel.setPosition({
		scoreboardLabel.getPosition().x + scoreboardLabel.getLocalBounds().size.x,
		scoreboardLabel.getPosition().y
	});
}

void Scoreboard::displayScore(int score){
	// Converts the score to a string
	std::stringstream ss;
    ss << score;
	scoreLabel.setString(ss.str());
}

void Scoreboard::draw(sf::RenderWindow& win){
	win.draw(scoreboardLabel);
	win.draw(scoreLabel);
}

// #region Getters/Setters

int Scoreboard::getBottomYCoordinate(){
	return scoreboardLabel.getPosition().y + scoreboardLabel.getLocalBounds().size.y;
}

// #endregion