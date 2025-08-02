/*
 * Scoreboard.cpp
 *
 *  Created on: 29.07.2025
 *      Author: Noah
 */

#include "Scoreboard.h"
#include "../../assets/AssetMappings.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

Scoreboard::Scoreboard(const sf::Font& font) :
	scoreboardLabel(font),
	scoreLabel(font)
	{ }
	

void Scoreboard::initialize(float space) {

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

void Scoreboard::draw(Layer& layer) const{
	layer.add_to_layer(scoreboardLabel);
	layer.add_to_layer(scoreLabel);
}

// #region Getters/Setters

const int Scoreboard::getBottomYCoordinate() const{
	return scoreboardLabel.getPosition().y + scoreboardLabel.getLocalBounds().size.y;
}

// #endregion