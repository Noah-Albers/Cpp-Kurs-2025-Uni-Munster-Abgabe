/*
 * Bullet.h
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#ifndef SRC_MODEL_BULLET_H_
#define SRC_MODEL_BULLET_H_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../properties/PropMoveable.h"
#include "../properties/PropAnimatedSprite.h"

class Bullet : public PropMoveable, public PropAnimatedSprite {
public:
	Bullet(const int x, const int y);
	virtual ~Bullet();
	
	// Updates the object
	void update(const float timePassed);
	
	// Position manipulation methods overwritten for PropMoveable
	virtual void setPosition(const sf::Vector2f position) override;
	virtual const sf::Vector2f getPosition() const override;
};

#endif /* SRC_MODEL_BULLET_H_ */
