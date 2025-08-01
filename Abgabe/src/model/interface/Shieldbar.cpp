/*
 * Shieldbar.cpp
 *
 *  Created on: 01.08.2025
 *      Author: Noah
 */

#include "Shieldbar.h"

#include "../../assets/AssetMappings.h"
#include <SFML/System/Vector2.hpp>

Shieldbar::Shieldbar(const int pos_x, const int pos_y) :
	PropSprite(ASSETS_SPRITE_SHIELD_BAR) {
	sprite.setPosition(sf::Vector2f(pos_x, pos_y));
}

Shieldbar::~Shieldbar() {}

void Shieldbar::drawBar(Layer& layer, float percentage){
	// Sets the frame that is to draw
	setFrame((getFrameAmount()-1) * percentage);
	
	layer.add_to_layer(sprite);
}
