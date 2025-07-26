/*
 * Alien.h
 *
 *  Created on: 26.07.2025
 *      Author: Olly
 */

#ifndef SRC_MODEL_ALIEN_H_
#define SRC_MODEL_ALIEN_H_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "./properties/PropMoveable.h"
#include "properties/PropSprite.h"

class Alien : public PropMoveable, public PropSprite {
public:
	Alien();
	virtual ~Alien();
	
	// Event: When the object shall update
	void update();
	
	// Position manipulation methods overwritten for PropMoveable
	virtual void setPosition(const sf::Vector2f position) override;
	virtual sf::Vector2f getPosition() override;
	
protected:    
};

#endif /* SRC_MODEL_ALIEN_H_ */
