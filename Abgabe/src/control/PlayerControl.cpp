/*
 * PlayerControl.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#include "PlayerControl.h"
#include <SFML/Window/Keyboard.hpp>
#include "../CMakeLists.h"
#include "properties/PropDrawable.h"
#include "../model/Constants.hpp"
#include "BulletControl.h"

PlayerControl::PlayerControl(Layer &layer) :
	PropDrawable(layer)
	{}
PlayerControl::~PlayerControl() {}

void PlayerControl::populate(BulletControl* bulletControl, ParticleControl* particleControl) {
	this->bulletControl = bulletControl;
	this->particleControl = particleControl;
}

void PlayerControl::update(const float time_passed){
	this->player.update(time_passed);
}

void PlayerControl::draw(){
	player.draw(layer);
}

void PlayerControl::damagePlayer(int amount){
	// If dead or invulnerable, he doesn't take damage
	if(player.isDead() || player.isInvulnerable()) return;
	
	player.setLifes(player.getLifes() - amount);
	player.setInvulnerable(2);
	
	// Handles death code
	if(player.isDead())
		onPlayerDeath(amount > 5);
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

void PlayerControl::keyStateChanged(bool is_now_pressed, sf::Keyboard::Key key) {
	// Prevents any inputs after the player has died
	if(player.isDead()) return;
	
	
	bool is_vertical = key == sf::Keyboard::Key::W || key == sf::Keyboard::Key::S;
	bool is_horizontal = key == sf::Keyboard::Key::A || key == sf::Keyboard::Key::D;
	
	if(is_vertical){
		this->player.setVerticalDirection(
				!is_now_pressed ? 			VerticalDirection::NONE :
				key == sf::Keyboard::Key::W ? 	VerticalDirection::UP   :
												VerticalDirection::DOWN
			);
	}else if(is_horizontal){
		this->player.setHorizontalDirection(
			!is_now_pressed ? 				HorizontalDirection::NONE  :
			key == sf::Keyboard::Key::D ? 		HorizontalDirection::RIGHT :
												HorizontalDirection::LEFT
		);
	}
	
	// All code below shall only execute on press
	if(!is_now_pressed) RETURN;
	
	// Spawns a bullet when space is pressed at the players position
	if (key == sf::Keyboard::Key::Space)
		bulletControl->spawnBulletAt(
			this->player.getPosition().x,
			this->player.getPosition().y
		);
		
	// TODO: Remove debug key
	if(key == sf::Keyboard::Key::Enter){
		
	}
}

// #region Getters/Setters

const Player& PlayerControl::getPlayer() const { return player; };

// #endregion