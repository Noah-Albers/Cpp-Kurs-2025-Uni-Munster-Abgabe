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
#include "../assets/AssetMappings.h"

PlayerControl::PlayerControl(Layer &layer) :
	PropDrawable(layer),
	lifes(constants::START_LIFES),
	blink_time_left(-1)
	{}
	
void PlayerControl::populate(BulletControl* bulletControl, ParticleControl* particleControl) {
	this->bulletControl = bulletControl;
	this->particleControl = particleControl;
}

void PlayerControl::update(float time_passed){
	this->player.update(time_passed);
	// count down blink time if it is set on a positive value
	if(blink_time_left >= 0)
		blink_time_left -= time_passed;
}

void PlayerControl::draw(){
	// Prevents the player from being drawn after he has died
	if(lifes <= 0) return;
	
	//if player lost life and blink time is set on positive value, player should blink for blink time seconds
	if(blink_time_left >= 0){
		int blink_int = (int)(blink_time_left *100);

		if (blink_int % 20 < 10) return; 

	}
	this->layer.add_to_layer(this->player.getSprite());
	
}

void PlayerControl::damagePlayer(int amount){
	if(lifes <= 0) return;
	
	bool hadStrongDamage = amount > 5;
	
	// Lets the player only lose life if he isn't blinking
	if(blink_time_left >= 0) return;
	if(amount > lifes) amount = lifes;
	
	lifes -= amount;
	blink_time_left = 2;
	
	// Handles death code
	if(lifes == 0)
		onPlayerDeath(hadStrongDamage);
}

void PlayerControl::onPlayerDeath(bool hadStrongDamage) {
	player.setHorizontalDirection(HorizontalDirection::NONE);
	player.setVerticalDirection(VerticalDirection::NONE);
	
	// Spawn death animation if player has died
	if(lifes == 0){
		int x = player.getPosition().x;
		int y = player.getPosition().y;
		
		if(hadStrongDamage)
			particleControl->spawnExplosionParticle(x, y);
		else
			particleControl->spawnPlayerDeathParticle(x, y);
	}
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

int PlayerControl::getLifes(){ return lifes; };
Player& PlayerControl::getPlayer(){ return player; };

// #endregion