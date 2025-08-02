/*
 * Health.h
 *
 *  Created on: 28.07.2025
 *      Author: Noah
 */

#ifndef SRC_MODEL_HEALTHBAR_H_
#define SRC_MODEL_HEALTHBAR_H_

#include "../properties/PropSprite.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "../../view/Layer.hpp"

class Healthbar : public PropSprite {
public:
	Healthbar(const int posX, const int posY);
	
	// Draws the health bar
	void drawBar(Layer& layer, const int lifes, const int maxlifes);
};

#endif /* SRC_MODEL_HEALTHBAR_H_ */
