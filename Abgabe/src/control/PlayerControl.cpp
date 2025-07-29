/*
 * PlayerControl.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#include "PlayerControl.h"
#include <SFML/Window/Keyboard.hpp>
#include "properties/PropDrawable.h"
#include "../model/Constants.hpp"
#include "BulletControl.h"

PlayerControl::PlayerControl(Layer &layer) :
	PropDrawable(layer),
	lifes(constants::START_LIFES)
	{}
	
void PlayerControl::populate(BulletControl* bulletControl, ParticleControl* particleControl) {
	this->bulletControl = bulletControl;
	this->particleControl = particleControl;
}

void PlayerControl::update(float time_passed){
	this->player.update(time_passed);
}

void PlayerControl::draw(){
	// Prevents the player from being drawn after he has died
	if(lifes <= 0) return;
	
	this->layer.add_to_layer(this->player.getSprite());
}

void PlayerControl::damagePlayer(int amount){
	lifes -= amount;
	
	// Spawn death animation if player has died
	if(lifes == 0)
		particleControl->spawnPlayerDeathParticle(player.getPosition().x, player.getPosition().y);
}

void PlayerControl::keyStateChanged(bool is_now_pressed, sf::Keyboard::Key key) {
	// Prevents any inputs after the player has died
	if(lifes <= 0) return;
	
	
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
	if(!is_now_pressed) return;
	
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

int PlayerControl::getLifes(){ return lifes; };
Player& PlayerControl::getPlayer(){ return player; };

// #endregion