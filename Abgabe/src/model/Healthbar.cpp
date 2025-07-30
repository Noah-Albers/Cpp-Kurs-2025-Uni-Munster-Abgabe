/*
 * Health.cpp
 *
 *  Created on: 28.07.2025
 *      Author: Noah
 */

#include "Healthbar.h"

#include "properties/PropSprite.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include "../assets/AssetMappings.h"

Healthbar::Healthbar(const int pos_x, const int pos_y) :
	PropSprite(ASSETS_SPRITE_HEALTH) {
		sprite.setPosition(sf::Vector2f({(float) pos_x, (float) pos_y}));
	}

	
void Healthbar::drawBar(Layer& layer, const int lifes, const int maxlifes) {
	// Moves the sprite for each heart and draws it
	// at the end resets its position to the start
	float pos = sprite.getPosition().x;
	for(int i=0;i<maxlifes;i++){
		// If the current iteration is a life that the player still has (false) or has lost (true)
		bool isLifeLost = i >= lifes;
		
		sprite.setTextureRect(sf::IntRect(
			{isLifeLost ? 7 : 0, 0},
			sprite.getTextureRect().size
		));
		
		// Moves the sprite along the x axis to draw the lifes
		sprite.setPosition({
			(float)(pos + (sprite.getTextureRect().size.x * sprite.getScale().x + 10) * i), 
			sprite.getPosition().y}
		);
		layer.add_to_layer(sprite);
	}
	sprite.setPosition({pos, sprite.getPosition().y});

}