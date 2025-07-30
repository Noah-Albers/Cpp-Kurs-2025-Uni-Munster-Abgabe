/*
 * Deathmessage.cpp
 *
 *  Created on: 30.07.2025
 *      Author: Noah
 */

#include "Deathmessage.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include "../model/Constants.hpp"

Deathmessage::Deathmessage(sf::Font& font) :
	titleLabel(font),
	subtitleLabel(font)
	{ }

void Deathmessage::initialize() {

	// Styles for the Title
	titleLabel.setString("Gameover");
	titleLabel.setFillColor(sf::Color::White);
    titleLabel.setStyle(sf::Text::Bold);
    titleLabel.setCharacterSize(70);
    
    // Positioning of the Title
    titleLabel.setOrigin(sf::Vector2f({
		titleLabel.getLocalBounds().size.x/2,
		titleLabel.getLocalBounds().size.y/2
	}));
	
	titleLabel.setPosition(sf::Vector2f({
		constants::GAME_WIDTH/2,
		constants::GAME_HEIGHT/2
	}));
    
    
    // Styles for the Subtitle
    subtitleLabel.setString("Press 'R' to restart");
    
    // Positioning for the Subtitle
    
    subtitleLabel.setOrigin(sf::Vector2f({
		subtitleLabel.getLocalBounds().size.x/2,
		subtitleLabel.getLocalBounds().size.y/2
	}));
	
	subtitleLabel.setPosition(sf::Vector2f({
		constants::GAME_WIDTH/2,
		constants::GAME_HEIGHT/2 + 80
	}));
}


void Deathmessage::draw(Layer& layer){
	layer.add_to_layer(titleLabel);
	layer.add_to_layer(subtitleLabel);
}