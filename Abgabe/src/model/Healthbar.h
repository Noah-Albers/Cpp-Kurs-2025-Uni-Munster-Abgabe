/*
 * Health.h
 *
 *  Created on: 28.07.2025
 *      Author: Noah
 */

#ifndef SRC_MODEL_HEALTHBAR_H_
#define SRC_MODEL_HEALTHBAR_H_

#include "./properties/PropSprite.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Healthbar : public PropSprite {
public:
	Healthbar(const int pos_x, const int pos_y);
	
	// Draws the health bar
	void drawBar(sf::RenderWindow& win, int lifes, int maxlifes);
};

#endif /* SRC_MODEL_HEALTHBAR_H_ */
