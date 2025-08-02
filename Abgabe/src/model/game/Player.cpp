/*
 * Player.cpp
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#include "Player.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>

#include "../Constants.hpp"
#include "../properties/PropMoveable.h"
#include "../properties/PropSprite.h"

#include "../../assets/AssetMappings.h"

Player::Player() :
	PropMoveable(constants::PLAYER_SPEED),
	PropSprite(ASSETS_SPRITE_PLAYER, true),
	shield(ASSETS_SPRITE_PLAYER_SHIELD, constants::ANIMATION_PLAYER_SHIELD_LENGTH),
	lifes(constants::PLAYER_START_LIFES),
	shieldbar(1),
	invulnTimeSec(-1)
    {
    // Positions the sprite
	setPosition({(float)(constants::GAME_WIDTH/2), (float)(constants::GAME_HEIGHT- sprite.getTextureRect().size.y)});
}
Player::~Player() {}

void Player::update(const float timePassed){
	this->updatePosition(timePassed);
	
	// Updates the invulnerability time of the player
	if(invulnTimeSec >= 0)
		invulnTimeSec -= timePassed;
	
	if(hasShield())
		shield.updateSprite(timePassed);
}

void Player::draw(Layer& layer) const{
	// Prevents the player from being drawn after he has died
	if(isDead()) return;
	
	// if player is invulnerable, he should blink
	if(isInvulnerable()){
		int blink_int = (int)(invulnTimeSec *100);

		if (blink_int % constants::PLAYER_BLINK_LENGTH*2 < constants::PLAYER_BLINK_LENGTH) return;
	}
	
	layer.add_to_layer(getSprite());
	
	if(hasShield())
		layer.add_to_layer(shield.getSprite());
}

void Player::setPosition(sf::Vector2f pos){
	// Ensures the player stays in the view
	if(pos.x < 0) pos.x = 0;
	if(pos.x > constants::GAME_WIDTH) pos.x = constants::GAME_WIDTH;
	if(pos.y < 0) pos.y = 0;
	if(pos.y > constants::GAME_HEIGHT) pos.y = constants::GAME_HEIGHT;
	
	sprite.setPosition(pos);
	shield.setPosition(pos);
}

// #region Getters/Setters

const int Player::getLifes() const { return lifes; };
const bool Player::isDead() const { return lifes <= 0; };
const bool Player::isInvulnerable() const { return invulnTimeSec >= 0; };
const sf::Vector2f Player::getPosition() const { return sprite.getPosition(); };
void Player::setLifes(int lifes) {
	if (lifes > constants::PLAYER_START_LIFES) lifes = constants::PLAYER_START_LIFES;
	if(lifes < 0) lifes = 0;
	this->lifes = lifes;
};
void Player::setInvulnerable(float timeSec) { invulnTimeSec = timeSec; };

const float Player::getShieldbar() const { return shieldbar; };
const bool Player::hasShield() const { return shieldbar >= 1; };
void Player::setShieldbar(float percentage) {
	if(percentage < 0) percentage = 0;
	if(percentage > 1) percentage = 1;
	shieldbar = percentage;
}

// #endregion

