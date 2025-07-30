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
#include "../properties/PropMoveable.h"
#include "AlienShield.h"
#include "../properties/PropSprite.h"

class Alien : public PropMoveable, public PropSprite {
public:
	Alien(const int x, const int y, const int lifes);
	virtual ~Alien();
	
	// Event: When the object shall update
	void update(const float time_passed);

	// Makes the alien change its direction
	void changeDirection();

	// Removes a life from the alien
	void removeLife();
	
	// Position manipulation methods overwritten for PropMoveable
	virtual void setPosition(const sf::Vector2f position) override;
	virtual const sf::Vector2f getPosition() const override;
	
	// Getters/Setters
	const sf::Sprite& getShieldSprite() const;
	const bool hasShield() const;
	const int getLifes() const;
		
protected:
	// Optional shield for the alien
	AlienShield* shield;
	int lifes;
	
	// Unallocates the shield if it exists
	void deleteShield();
};

#endif /* SRC_MODEL_ALIEN_H_ */
