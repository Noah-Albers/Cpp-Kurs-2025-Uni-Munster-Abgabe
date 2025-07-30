/*
 * Meteor.h
 *
 *  Created on: 27.07.2025
 *      Author: Alica
 */

#ifndef SRC_MODEL_METEOR_H_
#define SRC_MODEL_METEOR_H_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "properties/PropMoveable.h"
#include "properties/PropSprite.h"

class Meteor : public PropMoveable, public PropSprite {
public:
	Meteor(const int x, const int y);
	
	// Position manipulation methods overwritten for PropMoveable
	virtual void setPosition(const sf::Vector2f position) override;
	virtual const sf::Vector2f getPosition() const override;
};

#endif /* SRC_MODEL_BULLET_H_ */
