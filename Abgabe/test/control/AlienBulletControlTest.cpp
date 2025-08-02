/*
 * AlienBulletControlTest.cpp
 *
 *  Created on: 02.08.2025
 *      Author: Noah
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/View.hpp> 
#include "../../src/model/Constants.hpp"
#include "../CommonMockClasses.cpp"

#include "../../src/control/controls/AlienBulletControl.h"
#include "../../src/control/controls/AlienControl.h"
#include "../../src/control/controls/BulletControl.h"
#include "../../src/control/controls/LevelControl.h"
#include "../../src/control/controls/MeteorControl.h"
#include "../../src/control/controls/ParticleControl.h"
#include "../../src/control/controls/PlayerControl.h"
#include "../../src/control/controls/UIControl.h"


// ----------------------------------------
// Test Fixture
// ----------------------------------------

class AlienBulletControlTest :  public ::testing::Test { 
    public:
    AlienBulletControlTest() :
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
    AlienControl    alienControl;
    BulletControl       bulletControl;
    LevelControl        levelControl;
    MeteorControl       meteorControl;
    ParticleControl     particleControl;
    PlayerControl       playerControl;
    UIControl           uiControl;
};

// Ensures bullets can spawn
TEST_F(AlienBulletControlTest, spawnBullet) {
	ASSERT_EQ(alienBulletControl.getBullets().size(), (size_t)0);
	alienBulletControl.spawnBulletAt(10,10);
	ASSERT_EQ(alienBulletControl.getBullets().size(), (size_t)1);
	alienBulletControl.spawnBulletAt(20,20);
	ASSERT_EQ(alienBulletControl.getBullets().size(), (size_t)2);
}

// Ensures bullets are drawn
TEST_F(AlienBulletControlTest, draw){
	// Spawns some bullets
	alienBulletControl.spawnBulletAt(10,10);
	alienBulletControl.spawnBulletAt(20,10);
	alienBulletControl.spawnBulletAt(30,10);

	// Ensures all three are drawn
    EXPECT_CALL(layer, add_to_layer(testing::_))
        .Times(3);
    alienBulletControl.draw();
}

// Ensures bullets are updated (Can travel down)
TEST_F(AlienBulletControlTest, update_bullets_can_fall) {
	// Spawns a bullet
	alienBulletControl.spawnBulletAt(10,10);
	
	auto& bullet = alienBulletControl.getBullets().front();
	auto posA = bullet.getPosition();
	
	// Simulates a frame
	alienBulletControl.update(0.1);
	
	auto posB = bullet.getPosition();
	
	// Ensures the bullet has traveled down
	ASSERT_NEAR(posB.x, posA.x, 0.0001);
	ASSERT_GE(posB.y, posA.y + 0.1);
}

// Ensures bullets can damage the player
TEST_F(AlienBulletControlTest, update_damage_player_when_not_dead) {	
	// Spawn a bullet at the players position
	alienBulletControl.spawnBulletAt(playerControl.getPlayer().getPosition().x,playerControl.getPlayer().getPosition().y);
	
	// Ensures the player is alife and has a shield
    ASSERT_EQ(alienBulletControl.getBullets().size(),(size_t)1);
	ASSERT_TRUE(playerControl.getPlayer().hasShield());

	// Update the bullet
    alienBulletControl.update(0.1);
	
	// Ensures the player has lost the shield, bullet has despawned
	ASSERT_FALSE(playerControl.getPlayer().hasShield());
    ASSERT_TRUE(alienBulletControl.getBullets().empty());
}

// Ensures bullets can't interact with the player when he is dead
TEST_F(AlienBulletControlTest, update_damage_player_when_dead) {
	// Spawn a bullet at the players position
	alienBulletControl.spawnBulletAt(playerControl.getPlayer().getPosition().x,playerControl.getPlayer().getPosition().y);
    ASSERT_EQ(alienBulletControl.getBullets().size(),(size_t)1);
	
	// Ensures the is dead
	playerControl.killPlayer();

	// Update the bullet
    alienBulletControl.update(0.1);
	
	// Ensures the bullet is not affected
    ASSERT_EQ(alienBulletControl.getBullets().size(),(size_t)1);
}

// Ensures bullets are deleted when out of scope
TEST_F(AlienBulletControlTest, update_deletes_out_of_scope_bullets) {
	ASSERT_EQ(alienBulletControl.getBullets().size(), (size_t)0);
	
	// Spawns a bullet out of scope and ensures its despawned
    alienBulletControl.spawnBulletAt(constants::GAME_WIDTH/2,constants::GAME_HEIGHT+999);
	ASSERT_EQ(alienBulletControl.getBullets().size(), (size_t)1);
	
	alienBulletControl.update(0.1);
	
	ASSERT_EQ(alienBulletControl.getBullets().size(), (size_t)0);
}
