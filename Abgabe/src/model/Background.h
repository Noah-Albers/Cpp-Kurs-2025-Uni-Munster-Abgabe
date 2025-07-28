/*
 * Background.h
 *
 *  Created on: 28.07.2025
 *      Author: Noah
 */

#ifndef SRC_MODEL_BACKGROUND_H_
#define SRC_MODEL_BACKGROUND_H_

#include "./properties/PropSprite.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Background : public PropSprite {
public:
	Background(int windowSizeX);
	
	// Draws the background
	void draw(sf::RenderWindow& win);
	
	// Updates the object
	void update(float time_passed);
};

#endif /* SRC_MODEL_BACKGROUND_H_ */
