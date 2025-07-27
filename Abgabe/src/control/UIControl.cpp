/*
 * UIControl.cpp
 *
 *  Created on: 27.07.2025
 *      Author: snow
 */

#include "UIControl.h"
#include "../assets/AssetLoader.h"
#include <iostream>

UIControl::UIControl(sf::RenderWindow& window) :
	win(window),
	scoreboardLabel(AssetLoader::getInstance().getGameFont()),
	scoreLabel(AssetLoader::getInstance().getGameFont())
	{

	// Style options for the scoreboard
	scoreboardLabel.setString("Score: ");
    scoreboardLabel.setFillColor(sf::Color::White);
    scoreboardLabel.setStyle(sf::Text::Bold);
	scoreLabel.setFillColor(sf::Color::Red);

    // Set position of the text
    scoreboardLabel.setPosition({20,20});

	scoreLabel.setPosition({
		scoreboardLabel.getPosition().x + scoreboardLabel.getLocalBounds().size.x,
		scoreboardLabel.getPosition().y
	});

	// Sets the initial score
	setScore(0);
}

void UIControl::setScore(int newScore){
	score = newScore;
	
	std::stringstream ss;
    ss << score;
	scoreLabel.setString(ss.str());
}

void UIControl::draw() {
	win.draw(scoreboardLabel);
	win.draw(scoreLabel);
};
