/*
 * Background.cpp
 *
 *  Created on: 28.07.2025
 *      Author: Noah
 */

#include "Background.h"
#include "properties/PropSprite.h"

#include "../assets/AssetMappings.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "../model/Constants.hpp"

Background::Background() :
	PropSprite(ASSETS_SPRITE_BACKGROUND)
	{
	float scale = constants::GAME_WIDTH / (float)sprite.getTextureRect().size.x;
	sprite.setScale({scale, scale});	
	texture.setRepeated(true);
}

void Background::draw(Layer& layer) {
	// Draws to copys of the background
	layer.add_to_layer(sprite);
}

void Background::update(float time_passed) {
	
	// Calculates the next offset for the background by adding the time multiplied by a constant.
	// Because the background shall scroll into the negative direction, it inverts the current position to have the
	// calculation be positive and afterwards inverts it again
	int offset = (int)(-sprite.getTextureRect().position.y + time_passed * 100 * constants::BACKGROUND_SCROLL_SPEED) % sprite.getTextureRect().size.y;
	
	// Updates the visible texture area
	sprite.setTextureRect(sf::IntRect(
		{0,-offset},
		sprite.getTextureRect().size)
	);
}



