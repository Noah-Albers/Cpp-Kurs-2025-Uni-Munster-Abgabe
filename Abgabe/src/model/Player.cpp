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
#include "properties/PropMoveable.h"
#include "properties/PropSprite.h"

#include "../assets/AssetMappings.h"

Player::Player() :
	PropMoveable(3.5),
	PropSprite(ASSETS_SPRITE_PLAYER, true),
	lifes(constants::START_LIFES),
	invuln_time_sec(-1)
    {
		
    // Positions the sprite
    sprite.setPosition({0, constants::GAME_HEIGHT});
}
Player::~Player() {}

void Player::update(const float time_passed){
	this->updatePosition(time_passed);
	
	// Updates the invulnerability time of the player
	if(invuln_time_sec >= 0)
		invuln_time_sec -= time_passed;
}

void Player::draw(Layer& layer) const{
	// Prevents the player from being drawn after he has died
	if(isDead()) return;
	
	// if player is invulnerable, he should blink
	if(isInvulnerable()){
		int blink_int = (int)(invuln_time_sec *100);

		if (blink_int % 20 < 10) return;
	}
	
	layer.add_to_layer(getSprite());
}

void Player::setPosition(sf::Vector2f pos){
	// Ensures the player stays in the view
	if(pos.x < 0) pos.x = 0;
	if(pos.x > constants::GAME_WIDTH) pos.x = constants::GAME_WIDTH;
	if(pos.y < 0) pos.y = 0;
	if(pos.y > constants::GAME_HEIGHT) pos.y = constants::GAME_HEIGHT;
	
	sprite.setPosition(pos);
}

// #region Getters/Setters

const int Player::getLifes() const { return lifes; };
const bool Player::isDead() const { return lifes <= 0; };
const bool Player::isInvulnerable() const { return invuln_time_sec >= 0; };
const sf::Vector2f Player::getPosition() const { return sprite.getPosition(); };
void Player::setLifes(int lifes) {
	if(lifes < 0) lifes = 0;
	this->lifes = lifes;
};
void Player::setInvulnerable(float timeSec) { invuln_time_sec = timeSec; };

// #endregion

