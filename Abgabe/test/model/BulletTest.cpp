/*
 * BulletTest.cpp
 *
 *  Created on: 02.08.2025
 *      Author: Noah
 */
 
#include <SFML/System/Vector2.hpp>
#include <gtest/gtest.h>
#include "../../src/model/game/Bullet.h"

// Ensures the bullet constructor sets the correct position
TEST(BulletTest, constructor) {
	Bullet bullet(10, 20);
	
	ASSERT_EQ(bullet.getPosition(), sf::Vector2f(10, 20));
}

// Ensures the bullet update changes it's position correctly
TEST(BulletTest, update_changes_position_1) {
	int x = 5,y = 3;	
	
	Bullet bullet(x,y);
	ASSERT_EQ(bullet.getPosition(), sf::Vector2f(x,y));
	
	bullet.update(1);
	ASSERT_NE(bullet.getPosition(), sf::Vector2f(x,y));
}

// Duplicate of above to check multiple values
TEST(BulletTest, update_changes_position_2) {
	int x = 0,y = 0;
	
	Bullet bullet(x,y);
	ASSERT_EQ(bullet.getPosition(), sf::Vector2f(x,y));
	
	bullet.update(1);
	ASSERT_NE(bullet.getPosition(), sf::Vector2f(x,y));
}

// Duplicate of above to check multiple values
TEST(BulletTest, update_changes_position_3) {
	int x = 99999,y = 99999;
	
	Bullet bullet(x,y);
	ASSERT_EQ(bullet.getPosition(), sf::Vector2f(x,y));
	
	bullet.update(1);
	ASSERT_NE(bullet.getPosition(), sf::Vector2f(x,y));
}
