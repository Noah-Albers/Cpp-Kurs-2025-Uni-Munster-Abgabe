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
#include "../properties/PropMoveable.h"
#include "../properties/PropSprite.h"
#include "Shield.h"
#include "../../view/Layer.hpp"

class Player : public PropMoveable, public PropSprite {
public:
	Player();
	virtual ~Player();
	
	// Event: When the object shall update
	virtual void update(const float timePassed);
	
	// Event: Draws the player
	virtual void draw(Layer& layer) const;
	
	// Position manipulation methods overwritten for PropMoveable
	virtual void setPosition(const sf::Vector2f position) override;
	virtual const sf::Vector2f getPosition() const override;
	
	// Getters/Setters
	const int getLifes() const;
	void setLifes(int lifes);
	const bool isDead() const;
	void setInvulnerable(float timeSec);
	const bool isInvulnerable() const;
	const float getShieldbar() const;
	const bool hasShield() const;
	void setShieldbar(float percentage);
	
protected:
	// Shield sprite
	Shield shield;
	
	// How many lifes the player has left
	int lifes;

	// Percentage on how far the shield bar of is filled
	// From 0.00 to 1.00
	float shieldbar;

	// How long the player still is invincible (in seconds)
	float invulnTimeSec;
	
};

#endif /* SRC_MODEL_PLAYER_H_ */
