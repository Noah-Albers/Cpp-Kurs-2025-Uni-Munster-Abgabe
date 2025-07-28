/*
 * UIControl.cpp
 *
 *  Created on: 27.07.2025
 *      Author: Noah
 */

#include "UIControl.h"
#include "../assets/AssetLoader.h"
#include <SFML/Graphics/Rect.hpp>
#include "../model/Constants.hpp"
#include "Game.hpp"

UIControl::UIControl(sf::RenderWindow& window) :
	win(window),
	scoreboardLabel(AssetLoader::getInstance().getGameFont()),
	scoreLabel(AssetLoader::getInstance().getGameFont()),
	background(window.getSize().x)
	{
	
	// Style options for the scoreboard
	scoreboardLabel.setString("Score: ");
    scoreboardLabel.setFillColor(sf::Color::White);
    scoreboardLabel.setStyle(sf::Text::Bold);
	scoreLabel.setFillColor(sf::Color::Red);

	// Defines some space between the objects
	float space = 10;

    // Set positions
    scoreboardLabel.setPosition({space, space});

	scoreLabel.setPosition({
		scoreboardLabel.getPosition().x + scoreboardLabel.getLocalBounds().size.x,
		scoreboardLabel.getPosition().y
	});
	
	healthbar.getSprite().setPosition({
		space,
		scoreboardLabel.getPosition().y + scoreboardLabel.getLocalBounds().size.y + space * 2}
	);

	// Sets the initial score
	setScore(0);
}

void UIControl::update(float time_passed) {
	background.update(time_passed);
}

void UIControl::nextBackground(){
	background.setFrame(background.getFrame()+1);
}

void UIControl::setScore(int newScore){
	score = newScore;
	
	// Converts the score to a string
	std::stringstream ss;
    ss << score;
	scoreLabel.setString(ss.str());
}

void UIControl::draw() {
	background.draw(win);
	
	win.draw(scoreboardLabel);
	win.draw(scoreLabel);
	
	// Renders the health bar
	healthbar.drawBar(win,
		Game::getInstance().getPlayerControl().getLifes(),
		constants::START_LIFES
	);	
};
