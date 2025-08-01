/*
 * PlayerControl.h
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#ifndef SRC_CONTROL_PLAYERCONTROL_H_
#define SRC_CONTROL_PLAYERCONTROL_H_

#include <SFML/Graphics.hpp>
#include "../../view/Layer.hpp"
#include "../../model/game/Player.h"
#include "ParticleControl.h"
#include "../properties/PropDrawable.h"

// Declares classes to avoid circular dependencys
class BulletControl;

class PlayerControl : public PropDrawable {
public:
	PlayerControl(Layer &layer);
	virtual ~PlayerControl();
	
	// Part of setup
	// Its imperative to call this before anything else in this class
	void populate(BulletControl* bulletControl, ParticleControl* particleControl);
	
	
	// Event: When the game objects shall update
	void update(const float timePassed);
	
	/**
	 * Event: When a key is pressed or released.
	 * @param isNowPressed - stores if the given key got pressed (true) or released (false)
	 * @param keyCode - stores the given keycode. use sf::Keyboard::Key::<CODE> to check which key was pressed
	 */
	void keyStateChanged(bool isNowPressed, sf::Keyboard::Key keyCode);
	
	// Adds damage to the player
	void damagePlayer(int lifes = 1, bool wasStrong = false);
	
	// Kills the player
	virtual void killPlayer(bool wasStrong = false);
	
	virtual void draw() override;
	
	// Getters/Setters
	const Player& getPlayer() const;

protected:
	// Communication with other control's
	BulletControl* bulletControl;
	ParticleControl* particleControl;

	// Player object
	Player player;
	
	// Lets the player shot a bullet
	void shotBullet();
	
	// Handles the player death
	void onPlayerDeath(bool hadStrongDamage);
};

#endif /* SRC_CONTROL_PLAYERCONTROL_H_ */
