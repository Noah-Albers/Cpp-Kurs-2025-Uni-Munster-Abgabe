/**
 * AlienBulletTest.cpp
 * created on 31.07
 * author olly
 */

#include "../../src/model/game/AlienBullet.h"
#include "../../src/model/Constants.hpp"

#include <gtest/gtest.h>

// Ensures the constructor sets the position correctly
TEST(AlienBulletModelTest, constructorTest1) {
    AlienBullet ab = AlienBullet(10, 10);
    auto pos = ab.getPosition();

    ASSERT_EQ(pos, sf::Vector2f(10,10));
}

// Ensures the constructor sets the position correctly
TEST(AlienBulletModelTest, constructorTest2) {
    AlienBullet ab = AlienBullet(constants::GAME_WIDTH, constants::GAME_HEIGHT);
    auto pos = ab.getPosition();

    ASSERT_EQ(pos, sf::Vector2f(constants::GAME_WIDTH, constants::GAME_HEIGHT));
}

// Ensures the constructor sets the position correctly
TEST(AlienBulletModelTest, constructorTest3) {
    AlienBullet ab = AlienBullet(0, 0);
    auto pos = ab.getPosition();

    ASSERT_EQ(pos, sf::Vector2f(0,0));
}

// Ensures the update lets the bullets move
TEST(AlienBulletModelTest, updateTest1) {
    AlienBullet ab = AlienBullet(0, 0);
    auto posA = ab.getPosition();

    ab.update(0.5);
    auto posB = ab.getPosition();

    ASSERT_LE(posA.y, posB.y);
    ASSERT_NEAR(posA.x, posB.x, 0.00000000001);
}

// Ensures the update lets the bullets move
TEST(AlienBulletModelTest, updateTest2) {
    AlienBullet ab = AlienBullet(constants::GAME_WIDTH, constants::GAME_HEIGHT);
    auto posA = ab.getPosition();

    ab.update(0.1);
    auto posB = ab.getPosition();

    ASSERT_LE(posA.y, posB.y);
    ASSERT_NEAR(posA.x, posB.x, 0.00000000001);
}

// Ensures the update lets the bullets move
TEST(AlienBulletModelTest, updateTest3) {
    AlienBullet ab = AlienBullet(0, 0);
    auto posA = ab.getPosition();

    ab.update(1.0);
    auto posB = ab.getPosition();

    ASSERT_LE(posA.y, posB.y);
    ASSERT_NEAR(posA.x, posB.x, 0.00000000001);
}
