/*
 * PlayerControl.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#include "PlayerControl.h"
#include <SFML/Window/Keyboard.hpp>
#include "Game.hpp"
#include "properties/PropDrawable.h"
#include "../model/Constants.hpp"

PlayerControl::PlayerControl(Layer &layer) :
	PropDrawable(layer),
	lifes(constants::START_LIFES)
	{}
PlayerControl::~PlayerControl() {}

void PlayerControl::update(){
	this->player.update();
}

void PlayerControl::draw(){
	this->layer.add_to_layer(this->player.getSprite());
}

void PlayerControl::damagePlayer(int amount){
	lifes -= amount;
}

void PlayerControl::keyStateChanged(bool is_now_pressed, sf::Keyboard::Key key) {
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
	
	// Spawns a bullet when space is pressed
	if (key == sf::Keyboard::Key::Space)
		// TODO: Maybe at some point replace with constants or a calculation
		Game::getInstance().getBulletControl().spawnBulletAt(
			this->player.getPosition().x-14,
			this->player.getPosition().y-48
		);
		
	// TODO: Remove debug key
	if(key == sf::Keyboard::Key::Enter){
		
	}
}

// #region Getters/Setters

int PlayerControl::getLifes(){
	return lifes;
}



Player& PlayerControl::getPlayer(){
	return player;
}
// #endregion