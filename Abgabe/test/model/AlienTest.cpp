/*
 * AlienTest.cpp
 *
 *  Created on: 29.07.2025
 *      Author: Noah
 */
 
#include <SFML/System/Vector2.hpp>
#include "../../src/model/Alien.h"
#include "../../src/model/Constants.hpp"

#include <gtest/gtest.h>

// Checks that the aliens move when they are updated
TEST(AlienModelTest, update_moves_alien) {
	
	Alien alien(0,0,2);
	
	auto posA = alien.getPosition();
	
	alien.update(0.2);
	
	auto posB = alien.getPosition();
	
	ASSERT_NE(posA,posB);	
}

TEST(AlienModelTest, setPosition_out_of_bounce_negative){
	Alien alien(100,100,2);
	alien.setPosition(sf::Vector2f(-10, -10));	
	
	ASSERT_EQ(alien.getPosition(), sf::Vector2f(0,0));
}

TEST(AlienModelTest, setPosition_out_of_bounce_positive){
	Alien alien(100,100,2);
	alien.setPosition(sf::Vector2f(constants::GAME_WIDTH+10, constants::GAME_HEIGHT+10));	
	
	ASSERT_EQ(alien.getPosition(), sf::Vector2f(constants::GAME_WIDTH,constants::GAME_HEIGHT));
}

TEST(AlienModelTest, setPosition_change_direction){
	Alien alien(100,100,2);
	auto dir = alien.getHorizontalDirection();
	alien.changeDirection();
	ASSERT_NE(dir, alien.getHorizontalDirection());
	alien.changeDirection();
	ASSERT_EQ(dir, alien.getHorizontalDirection());
}

TEST(AlienModelTest, removeLife){
	Alien alien(100,100,2);
	ASSERT_EQ(alien.getLifes(), 2);
	alien.removeLife();
	ASSERT_EQ(alien.getLifes(), 1);
}


