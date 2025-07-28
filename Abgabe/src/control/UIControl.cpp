/*
 * UIControl.cpp
 *
 *  Created on: 27.07.2025
 *      Author: Noah
 */

#include "UIControl.h"
#include "../assets/AssetLoader.h"
#include <SFML/Graphics/Rect.hpp>
#include <iostream>
#include "../model/Constants.hpp"
#include "Game.hpp"

UIControl::UIControl(sf::RenderWindow& window) :
	win(window),
	scoreboardLabel(AssetLoader::getInstance().getGameFont()),
	scoreLabel(AssetLoader::getInstance().getGameFont()),
	healthTexture(),
	healthSprite(healthTexture)
	{
	// load the health texture
    if (!healthTexture.loadFromFile("assets/sprites/health.png"))
        throw std::invalid_argument("Spritesheet not found");
    // set up sprite
    healthSprite.setTexture(healthTexture);
    healthSprite.setTextureRect(sf::IntRect({0, 0}, {7, 7}));
	healthSprite.setScale({6, 6});

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
	
	healthSprite.setPosition({
		space,
		scoreboardLabel.getPosition().y + scoreboardLabel.getLocalBounds().size.y + space * 2}
	);

	// Sets the initial score
	setScore(0);
}

void UIControl::setScore(int newScore){
	score = newScore;
	
	// Converts the score to a string
	std::stringstream ss;
    ss << score;
	scoreLabel.setString(ss.str());
}

void UIControl::draw() {
	win.draw(scoreboardLabel);
	win.draw(scoreLabel);
	
	// Gets the player lifes
	int currentLifes = Game::getInstance().getPlayerControl().getLifes();
	
	// Moves the sprite for each heart and draws it
	// at the end resets its position to the start
	float pos = healthSprite.getPosition().x;
	for(int i=0;i<constants::START_LIFES;i++){
		// If the current iteration is a life that the player still has (false) or has lost (true)
		bool isLifeLost = i >= currentLifes;
		
		healthSprite.setTextureRect(sf::IntRect(
			{isLifeLost ? 7 : 0, 0},
			healthSprite.getTextureRect().size
		));
		
		// Moves the sprite along the x axis to draw the lifes
		healthSprite.setPosition({
			(float)(pos + (healthSprite.getTextureRect().size.x * healthSprite.getScale().x + 10) * i), 
			healthSprite.getPosition().y}
		);
		win.draw(healthSprite);
	}
	healthSprite.setPosition({pos , healthSprite.getPosition().y});
	
};
