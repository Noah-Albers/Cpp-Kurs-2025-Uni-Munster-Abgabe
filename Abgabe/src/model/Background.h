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
#include "../view/Layer.hpp"

class Background : public PropSprite {
public:
	Background();
	
	// Draws the background
	void draw(Layer& layer);
	
	// Updates the object
	void update(float time_passed);
};

#endif /* SRC_MODEL_BACKGROUND_H_ */
