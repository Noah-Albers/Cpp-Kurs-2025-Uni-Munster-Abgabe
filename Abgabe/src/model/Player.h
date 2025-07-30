/*
 * Player.h
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#ifndef SRC_MODEL_PLAYER_H_
#define SRC_MODEL_PLAYER_H_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "./properties/PropMoveable.h"
#include "properties/PropSprite.h"

class Player : public PropMoveable, public PropSprite {
public:
	Player();
	virtual ~Player();
	
	// Event: When the object shall update
	void update(float time_passed);
	
	// Position manipulation methods overwritten for PropMoveable
	virtual void setPosition(const sf::Vector2f position) override;
	virtual sf::Vector2f getPosition() override;
};

#endif /* SRC_MODEL_PLAYER_H_ */
