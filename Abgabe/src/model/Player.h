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
#include "../view/Layer.hpp"

class Player : public PropMoveable, public PropSprite {
public:
	Player();
	virtual ~Player();
	
	// Event: When the object shall update
	void update(float time_passed);
	
	// Event: Draws the player
	void draw(Layer& layer);
	
	// Position manipulation methods overwritten for PropMoveable
	virtual void setPosition(const sf::Vector2f position) override;
	virtual sf::Vector2f getPosition() override;
	
	// Getters/Setters
	int getLifes() const;
	void setLifes(int lifes);
	bool isDead();
	void setInvulnerable(float timeSec);
	bool isInvulnerable();
	
protected:
	// How many lifes the player has left
	int lifes;

	// How long the player still is invincible (in seconds)
	float invuln_time_sec;
};

#endif /* SRC_MODEL_PLAYER_H_ */
