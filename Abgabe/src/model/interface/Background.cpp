/*
 * Background.cpp
 *
 *  Created on: 28.07.2025
 *      Author: Noah
 */

#include "Background.h"
#include "../properties/PropSprite.h"

#include "../../assets/AssetMappings.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../../model/Constants.hpp"

Background::Background() :
	PropSprite(ASSETS_SPRITE_BACKGROUND),
	transitionPercentage(-1)
	{
	// Calculates the scale-factor which is needed to get the background to cover the whole width of the screen
	float scale = constants::GAME_WIDTH / (float)sprite.getTextureRect().size.x;
	sprite.setScale({scale, scale});	
	// Enables texture-repeating on the sprite the ensure it can be moved by just changing the viewport
	texture.setRepeated(true);
}

void Background::draw(Layer& layer) {
	
	if(isTransitioning()){
		// Caluclates the rgba-level (0-255) from the render-percantage
		int rgbaLvl = 255 * transitionPercentage;
	
		// Renders the old frame at a reducing alpha-level
		sprite.setColor(sf::Color(255,255,255, 255 - rgbaLvl));
		layer.add_to_layer(sprite);
			
		// Advances the frame
		auto frame = getFrame();
		setFrame(frame+1);
		
		// Renders the new frame at a increasing alpha-level
		sprite.setColor(sf::Color(255,255,255, rgbaLvl));
		layer.add_to_layer(sprite);
		
		// Reset frame and alpha level
		setFrame(frame);		
		sprite.setColor(sf::Color(255,255,255, 255));
	}else {
		// Draws the normal background
		layer.add_to_layer(sprite);
	}
}

void Background::update(const float timePassed) {
	
	// Calculates the next offset for the background by adding the time multiplied by a constant.
	// Because the background shall scroll into the negative direction, it inverts the current position to have the
	// calculation be positive and afterwards inverts it again
	int offset = (int)(-sprite.getTextureRect().position.y + timePassed * 100 * constants::BACKGROUND_SCROLL_SPEED) % sprite.getTextureRect().size.y;
	
	// Updates the visible texture area
	sprite.setTextureRect(sf::IntRect(
		{sprite.getTextureRect().position.x,-offset},
		sprite.getTextureRect().size)
	);
	
	if(isTransitioning())
		updateTransition(timePassed);
}

void Background::updateTransition(const float timePassed){
	transitionPercentage += timePassed * constants::BACKGROUND_TRANSITION_SPEED;
	
	// Finishes the transition by advancing the frame
	if(transitionPercentage > 1){
		transitionPercentage = -1;
		setFrame(getFrame()+1);
		return;
	}
}

void Background::transitionToNextBackground() {
	// If the background is still transitioning, this will finish the transition.
	// This will then skip the transition and start with the next one
	if(isTransitioning())
		setFrame(getFrame()+1);
	
	transitionPercentage = 0;
}

// #region Getters/Setters

const bool Background::isTransitioning() const { return transitionPercentage >= 0; };

// #endregion