/*
 * AlienShield.h
 *
 *  Created on: 30.07.2025
 *      Author: snow
 */

#ifndef SRC_MODEL_ALIENSHIELD_H_
#define SRC_MODEL_ALIENSHIELD_H_

#include "properties/PropAnimatedSprite.h"
#include <SFML/System/Vector2.hpp>
class AlienShield : public PropAnimatedSprite {
public:
	AlienShield();
	
	void setPosition(sf::Vector2f pos);
};

#endif /* SRC_MODEL_ALIENSHIELD_H_ */
