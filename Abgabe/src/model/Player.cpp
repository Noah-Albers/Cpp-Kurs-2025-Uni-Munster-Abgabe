/*
 * Player.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#include "Player.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include "Constants.hpp"

Player::Player() :
	texture(),
    sprite(texture),
    h_dir(HorizontalDirection::NONE),
    v_dir(VerticalDirection::NONE),
    speed(5)
    {
		
    // load texture
    if (!texture.loadFromFile(("assets/sprites/player_default.png")))
        throw std::invalid_argument("Spritesheet not found");
    // set up sprite
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect({0, 0}, {48, 48}));
    sprite.setOrigin({24,24});
    sprite.setPosition({0, constants::VIEW_HEIGHT});
}

void Player::update(){
	int by_x=0, by_y=0;
	if(v_dir != VerticalDirection::NONE)
		by_y = v_dir == VerticalDirection::DOWN ? 1 : -1;
	if(h_dir != HorizontalDirection::NONE)
		by_x = h_dir == HorizontalDirection::RIGHT ? 1 : -1;
	
	if(by_x != 0 || by_y != 0)
		moveBy(by_x * this->speed,by_y * this->speed);
}


void Player::moveBy(int x, int y){
	auto new_pos = sprite.getPosition() + sf::Vector2f(x,y);
	
	// Ensures the player can't go outside the field
	if(new_pos.x < 0 || new_pos.x > constants::VIEW_WIDTH) return;
	if(new_pos.y < 0 || new_pos.y > constants::VIEW_HEIGHT) return;
	
	sprite.setPosition(new_pos);
}

// #region Getters and setters
	
void Player::setVerticalDirection(VerticalDirection dir) { v_dir = dir; }
void Player::setHorizontalDirection(HorizontalDirection dir) { h_dir = dir; }

sf::Sprite Player::getSprite(){ return sprite; }
	
// #endregion


Player::~Player() {
	// TODO Auto-generated destructor stub
}

