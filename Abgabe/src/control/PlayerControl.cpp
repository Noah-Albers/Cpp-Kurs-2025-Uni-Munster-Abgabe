/*
 * PlayerControl.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#include "PlayerControl.h"
#include <SFML/Window/Keyboard.hpp>

PlayerControl::PlayerControl(Layer &layer) : layer(layer) {
	// TODO Auto-generated constructor stub

}

void PlayerControl::update(){
	this->player.update();
}

void PlayerControl::draw(){
	this->layer.add_to_layer(this->player.getSprite());
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
}

PlayerControl::~PlayerControl() {
	// TODO Auto-generated destructor stub
}

