/*
 * BulletControlTest.cpp
 *
 *  Created on: 02.08.2025
 *      Author: Noah
 */

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../../src/control/controls/AlienBulletControl.h"
#include "../../src/control/controls/AlienControl.h"
#include "../../src/control/controls/BulletControl.h"
#include "../../src/control/controls/LevelControl.h"
#include "../../src/control/controls/MeteorControl.h"
#include "../../src/control/controls/ParticleControl.h"
#include "../../src/control/controls/PlayerControl.h"
#include "../../src/control/controls/UIControl.h"
#include "../../src/model/Constants.hpp"
#include "../CommonMockClasses.cpp"

class BulletControlTest :  public ::testing::Test { 
public:
    BulletControlTest() :
        win(sf::VideoMode({10, 10}), "Dummy"),
        layer(win),
        layerbg(win),
        alienBulletControl(layer),
        alienControl(layer),
        bulletControl(layer),
        levelControl(),
        meteorControl(layer),
        particleControl(layer),
        playerControl(layer),
        uiControl(layer, layerbg)
        {
        alienBulletControl.populate(&playerControl);
	    alienControl.populate(&alienBulletControl, &levelControl, &playerControl);
	    bulletControl.populate(&alienControl, &meteorControl);
	    meteorControl.populate(&playerControl, &particleControl);
	    playerControl.populate(&bulletControl, &particleControl);
	    uiControl.populate(&playerControl);
        levelControl.populate(&alienControl, &uiControl);	
    };

    sf::RenderWindow win;
    MockLayer layer;
    MockLayer layerbg;
    AlienBulletControl  alienBulletControl;
    AlienControl        alienControl;
    BulletControl       bulletControl;
    LevelControl        levelControl;
    MeteorControl       meteorControl;
    ParticleControl     particleControl;
    PlayerControl       playerControl;
    UIControl           uiControl;
};


// Ensures bullets can spawn
TEST_F(BulletControlTest, spawnBullet) {
	ASSERT_EQ(bulletControl.getBullets().size(), (size_t)0);
	bulletControl.spawnBulletAt(10,10);
	ASSERT_EQ(bulletControl.getBullets().size(), (size_t)1);
	bulletControl.spawnBulletAt(20,20);
	ASSERT_EQ(bulletControl.getBullets().size(), (size_t)2);
}

// Ensures bullets are drawn
TEST_F(BulletControlTest, draw){
	// Spawns some bullets
	bulletControl.spawnBulletAt(10,10);
	bulletControl.spawnBulletAt(20,10);
	bulletControl.spawnBulletAt(30,10);

	// Ensures all three are drawn
    EXPECT_CALL(layer, add_to_layer(testing::_))
        .Times(3);
    bulletControl.draw();
}

// Ensures bullets are updated (Can travel up)
TEST_F(BulletControlTest, update_bullets_can_fall) {
	// Spawns a bullet
	bulletControl.spawnBulletAt(10,10);
	
	auto& bullet = bulletControl.getBullets().front();
	auto posA = bullet.getPosition();
	
	// Simulates a frame
	bulletControl.update(0.1);
	
	auto posB = bullet.getPosition();
	
	// Ensures the bullet has traveled up
	ASSERT_NEAR(posB.x, posA.x, 0.0001);
	ASSERT_LE(posB.y, posA.y + 0.1);
}

// Ensures bullets can damage aliens, despawns them and removes the bullet
TEST_F(BulletControlTest, update_damage_aliens) {
	// Spawns an alien and a bullet in the same place
	alienControl.spawnAlien(0, 0, 1, 0);
	bulletControl.spawnBulletAt(0,0);
	
    ASSERT_EQ(alienControl.getAliens().size(),(size_t)1);
    ASSERT_EQ(bulletControl.getBullets().size(),(size_t)1);
	
	// Simulates an update
	bulletControl.update(0);
	alienControl.update(0);
	
	// Ensures both things have been removed
    ASSERT_EQ(alienControl.getAliens().size(),(size_t)0);
    ASSERT_EQ(bulletControl.getBullets().size(),(size_t)0);
}

// Ensures bullets are deleted by meteors
TEST_F(BulletControlTest, update_bullet_removed_by_meteor) {
	// Spawns a meteor and a bullet in the same place
	meteorControl.spawnMeteorAt(0, 0);
	const Meteor& meteor = meteorControl.getMeteors().front();
	bulletControl.spawnBulletAt(0, -meteor.getSprite().getTextureRect().size.y);
	
    ASSERT_EQ(meteorControl.getMeteors().size(),(size_t)1);
    ASSERT_EQ(bulletControl.getBullets().size(),(size_t)1);
	
	// Simulates an update
	bulletControl.update(0);
	
	// Ensures only the bullet has been removed
    ASSERT_EQ(meteorControl.getMeteors().size(),(size_t)1);
    ASSERT_EQ(bulletControl.getBullets().size(),(size_t)0);
}


// Ensures bullets are deleted when out of scope
TEST_F(BulletControlTest, update_deletes_out_of_scope_bullets) {
	ASSERT_EQ(bulletControl.getBullets().size(), (size_t)0);
	
	// Spawns a bullet out of scope and ensures its despawned
    bulletControl.spawnBulletAt(constants::GAME_WIDTH/2,-999);
	ASSERT_EQ(bulletControl.getBullets().size(), (size_t)1);
	
	bulletControl.update(0);
	
	ASSERT_EQ(bulletControl.getBullets().size(), (size_t)0);
}
