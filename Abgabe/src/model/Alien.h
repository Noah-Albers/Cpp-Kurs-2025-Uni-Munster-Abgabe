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
#include "properties/PropAnimatedSprite.h"
#include "properties/PropSprite.h"

class Alien : public PropMoveable, public PropSprite {
public:
	Alien(const int x, const int y, const int lifes);
	virtual ~Alien();
	
	// Event: When the object shall update
	void update(float time_passed);
	
	// Position manipulation methods overwritten for PropMoveable
	virtual void setPosition(const sf::Vector2f position) override;
	virtual sf::Vector2f getPosition() override;

	void changeDirection();

	sf::Sprite getShieldSprite();

	int getLifes();
	void removeLife();
protected: 

private:
	PropAnimatedSprite shieldSprite;
	int lifes;
};

#endif /* SRC_MODEL_ALIEN_H_ */
