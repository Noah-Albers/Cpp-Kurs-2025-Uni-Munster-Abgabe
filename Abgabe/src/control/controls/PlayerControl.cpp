/*
 * PlayerControl.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#include "PlayerControl.h"
#include <SFML/Window/Keyboard.hpp>
#include "../../CMakeLists.h"
#include "../properties/PropDrawable.h"
#include "../../model/Constants.hpp"
#include "BulletControl.h"

PlayerControl::PlayerControl(Layer &layer) :
	PropDrawable(layer)
	{}
PlayerControl::~PlayerControl() {}

void PlayerControl::populate(BulletControl* bulletControl, ParticleControl* particleControl) {
	this->bulletControl = bulletControl;
	this->particleControl = particleControl;
}

void PlayerControl::update(const float timePassed){
	this->player.update(timePassed);
	
	// Slowly fills the shieldbar
	if(player.getShieldbar() < 1)
		player.setShieldbar(player.getShieldbar() + timePassed * constants::PLAYER_SHIELD_FILL_FREQUENCY);
}

void PlayerControl::draw(){
	player.draw(layer);
}

void PlayerControl::killPlayer(bool wasStrong) {
	player.setInvulnerable(-1);
	player.setShieldbar(0);
	damagePlayer(player.getLifes(), wasStrong);
}

void PlayerControl::damagePlayer(int amount, bool wasStrong){
	// If dead or invulnerable, he doesn't take damage
	if(player.isDead() || player.isInvulnerable()) return;
	
	if(player.hasShield())
		player.setShieldbar(0);
	else
		player.setLifes(player.getLifes() - amount);
	
	player.setInvulnerable(constants::INVULNERABILITY_TIME);
	
	// Handles death code
	if(player.isDead())
		onPlayerDeath(wasStrong);
}

void PlayerControl::onPlayerDeath(bool hadStrongDamage) {
	player.setHorizontalDirection(HorizontalDirection::NONE);
	player.setVerticalDirection(VerticalDirection::NONE);
	
	int x = player.getPosition().x;
	int y = player.getPosition().y;
	
	if(hadStrongDamage)
		particleControl->spawnExplosionParticle(x, y);
	else
		particleControl->spawnPlayerDeathParticle(x, y);
}

void PlayerControl::keyStateChanged(bool isNowPressed, sf::Keyboard::Key key) {
	// Prevents any inputs after the player has died
	if(player.isDead()) return;
	
	
	bool isVertical = key == sf::Keyboard::Key::W || key == sf::Keyboard::Key::S;
	bool isHorizontal = key == sf::Keyboard::Key::A || key == sf::Keyboard::Key::D;
	
	if(isVertical){
		this->player.setVerticalDirection(
				!isNowPressed ? 			VerticalDirection::NONE :
				key == sf::Keyboard::Key::W ? 	VerticalDirection::UP   :
												VerticalDirection::DOWN
			);
	}else if(isHorizontal){
		this->player.setHorizontalDirection(
			!isNowPressed ? 				HorizontalDirection::NONE  :
			key == sf::Keyboard::Key::D ? 		HorizontalDirection::RIGHT :
												HorizontalDirection::LEFT
		);
	}
	
	// All code below shall only execute on press
	if(!isNowPressed) RETURN;
	
	// Spawns a bullet when space is pressed at the players position
	if (key == sf::Keyboard::Key::Space)
		bulletControl->spawnBulletAt(
			this->player.getPosition().x,
			this->player.getPosition().y
		);
}

// #region Getters/Setters

const Player& PlayerControl::getPlayer() const { return player; };

// #endregion