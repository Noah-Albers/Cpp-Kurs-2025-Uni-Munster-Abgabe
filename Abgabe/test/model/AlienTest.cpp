/*
 * AlienTest.cpp
 *
 *  Created on: 31.07.2025
 *      Author: Olly
 */
 
#include <SFML/System/Vector2.hpp>
#include "../../src/model/game/Alien.h"
#include "../../src/model/Constants.hpp"

#include <gtest/gtest.h>

// Checks that the aliens move when they are updated
TEST(AlienModelTest, updateNormalSpeed) {
	
	Alien alien(0,0,2, 1.0);
	
	auto posA = alien.getPosition();
	
	alien.update(0.2);
	
	auto posB = alien.getPosition();
	
	ASSERT_NE(posA,posB);	
}

TEST(AlienModelTest, updateNoSpeed) {
	Alien alien (10, 10, 1, 0);
	auto posA = alien.getPosition();

	alien.update(0.2);
	auto posB = alien.getPosition();

	ASSERT_EQ(posA, posB);
}

TEST(AlienModelTest, updateSuperFastSpeed) {
	Alien alien (10, 10, 1, 9876123456789.0);
	auto posA = alien.getPosition();

	alien.update(0.5);
	auto posB = alien.getPosition();

	ASSERT_NE(posA, posB);
}

TEST(AlienModelTest, setPosition_out_of_bounce_negative){
	Alien alien(100,100,2, 1.0);
	alien.setPosition(sf::Vector2f(-10, -10));	
	
	ASSERT_EQ(alien.getPosition(), sf::Vector2f(0,-10));
}

TEST(AlienModelTest, setPosition_out_of_bounce_positive){
	Alien alien(100,100,2, 1.0);
	alien.setPosition(sf::Vector2f(constants::GAME_WIDTH+10, constants::GAME_HEIGHT+10));	
	
	ASSERT_EQ(alien.getPosition(), sf::Vector2f(constants::GAME_WIDTH,constants::GAME_HEIGHT));
}

TEST(AlienModelTest, setPositionNormal){
	Alien alien(100,100,2, 1.0);
	alien.setPosition(sf::Vector2f(constants::GAME_WIDTH / 2, constants::GAME_HEIGHT / 2));	
	
	ASSERT_EQ(alien.getPosition(), sf::Vector2f(constants::GAME_WIDTH / 2,constants::GAME_HEIGHT / 2));
}

TEST(AlienModelTest, changeDirection){
	Alien alien(100, 100, 2, 1.0);
	auto dir = alien.getHorizontalDirection();
	alien.changeDirection();
	ASSERT_NE(dir, alien.getHorizontalDirection());
	alien.changeDirection();
	ASSERT_EQ(dir, alien.getHorizontalDirection());
}

TEST(AlienModelTest, removeLifeShield1) {
	Alien alien(100, 100, 0, 1.0);
	ASSERT_FALSE(alien.hasShield());
	ASSERT_EQ(alien.getLifes(), 0);

	alien.removeLife();
	ASSERT_FALSE(alien.hasShield());
	ASSERT_EQ(alien.getLifes(), 0);
}

TEST(AlienModelTest, removeLifeShield2) {
	Alien alien(100, 100, 1, 1.0);
	ASSERT_FALSE(alien.hasShield());
	ASSERT_EQ(alien.getLifes(), 1);

	alien.removeLife();
	ASSERT_FALSE(alien.hasShield());
	ASSERT_EQ(alien.getLifes(), 0);

	alien.removeLife();
	ASSERT_FALSE(alien.hasShield());
	ASSERT_EQ(alien.getLifes(), 0);
}

TEST(AlienModelTest, removeLifeShield3) {
	Alien alien(100, 100, 3, 1.0);
	ASSERT_TRUE(alien.hasShield());
	ASSERT_EQ(alien.getLifes(), 3);

	alien.removeLife();
	ASSERT_TRUE(alien.hasShield());
	ASSERT_EQ(alien.getLifes(), 2);

	alien.removeLife();
	ASSERT_FALSE(alien.hasShield());
	ASSERT_EQ(alien.getLifes(), 1);

	alien.removeLife();
	ASSERT_FALSE(alien.hasShield());
	ASSERT_EQ(alien.getLifes(), 0);
}


