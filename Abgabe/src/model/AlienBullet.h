/*
 * AlienBullet.h
 *
 *  Created on: 28.07.2025
 *      Author: Olly
 */

#ifndef SRC_MODEL_ALIENBULLET_H_
#define SRC_MODEL_ALIENBULLET_H_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "properties/PropMoveable.h"
#include "properties/PropAnimatedSprite.h"

class AlienBullet : public PropMoveable, public PropAnimatedSprite {
public:
	AlienBullet(const int x, const int y);
	virtual ~AlienBullet();
	
	// Updates the object
	void update(float time_passed);
	
	// Position manipulation methods overwritten for PropMoveable
	virtual void setPosition(const sf::Vector2f position) override;
	virtual sf::Vector2f getPosition() override;
private:
};

#endif /* SRC_MODEL_ALIENBULLET_H_ */
