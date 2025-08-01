/*
 * Shieldbar.h
 *
 *  Created on: 01.08.2025
 *      Author: Noah
 */

#ifndef SRC_MODEL_INTERFACE_SHIELDBAR_H_
#define SRC_MODEL_INTERFACE_SHIELDBAR_H_

#include "../properties/PropSprite.h"
#include "../../view/Layer.hpp"

class Shieldbar : public PropSprite {
public:
	Shieldbar(const int pos_x, const int pos_y);
	virtual ~Shieldbar();
	
	// Draws the shield bar
	void drawBar(Layer& layer, float fillPercentage);
};

#endif /* SRC_MODEL_INTERFACE_SHIELDBAR_H_ */
