/**
 *
 * MeteorControlTest.cpp
 *
 *  Created on 01.08.2025
 * 		Author: Alice
 *
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


class MeteorControlTest :  public ::testing::Test { 
public:
    MeteorControlTest() :
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

// Ensures that meteors can spawn
TEST_F(MeteorControlTest, spawnMeteor){
	ASSERT_EQ(meteorControl.getMeteors().size(), (size_t)0);
	meteorControl.spawnMeteorAt(10, 10);
	ASSERT_EQ(meteorControl.getMeteors().size(), (size_t)1);
	meteorControl.spawnMeteorAt(20, 20);
	ASSERT_EQ(meteorControl.getMeteors().size(), (size_t)2);
}

// Ensures meteors are drawn
TEST_F(MeteorControlTest, draw){
	// Spawns some meteors
    meteorControl.spawnMeteorAt(constants::GAME_WIDTH/2,constants::GAME_HEIGHT/2);
    meteorControl.spawnMeteorAt(constants::GAME_WIDTH,constants::GAME_HEIGHT);
    meteorControl.spawnMeteorAt(0,0);

	// Ensures all three are drawn
    EXPECT_CALL(layer, add_to_layer(testing::_))
        .Times(3);
    meteorControl.draw();
}

// Ensures meteors can fall down
TEST_F(MeteorControlTest, update_meteors_can_fall) {
	// Spawns a meteor
	meteorControl.spawnMeteorAt(10,10);
	
	auto& m = meteorControl.getMeteors().front();
	auto posA = m.getPosition();
	
	// Simulates a frame
	meteorControl.update(0.1);
	
	auto posB = m.getPosition();
	
	// Ensures the meteor has fallen
	ASSERT_NEAR(posB.x, posA.x, 0.0001);
	ASSERT_GE(posB.y, posA.y + 0.1);
}

// Ensures meteors can damage the player
// and spawn a particle while doing it
TEST_F(MeteorControlTest, update_damage_player_when_not_dead) {
	auto prevSize = particleControl.getParticles().size();
	
	// Spawn a meteor at the players potion
	meteorControl.spawnMeteorAt(playerControl.getPlayer().getPosition().x,playerControl.getPlayer().getPosition().y);
	
	// Ensures the player is alife and has a shield
    ASSERT_EQ(meteorControl.getMeteors().size(),(size_t)1);
	ASSERT_TRUE(playerControl.getPlayer().hasShield());

	// Update the meteor
    meteorControl.update(0.1);
	
	// Ensures the player has lost the shield, meteor has despawned
	// and a particle has been added
	ASSERT_FALSE(playerControl.getPlayer().hasShield());
    ASSERT_TRUE(meteorControl.getMeteors().empty());
    ASSERT_EQ(particleControl.getParticles().size(), prevSize+1);
}

// Ensures meteors can't interact with the player when he is dead
TEST_F(MeteorControlTest, update_damage_player_when_dead) {
	// Spawn a meteor at the players potion
	meteorControl.spawnMeteorAt(playerControl.getPlayer().getPosition().x,playerControl.getPlayer().getPosition().y);
    ASSERT_EQ(meteorControl.getMeteors().size(), (size_t)1);
    
	// Kills the player
	playerControl.killPlayer();
	
	auto prevSize = particleControl.getParticles().size();

	// Update the meteor
    meteorControl.update(0.1);
	
	// Ensure the meteor still exists
    ASSERT_EQ(meteorControl.getMeteors().size(), (size_t)1);
    ASSERT_EQ(particleControl.getParticles().size(), prevSize);
}

// Ensures meteors are deleted when out of scope
TEST_F(MeteorControlTest, update_deletes_out_of_scope_meteors) {
	ASSERT_EQ(meteorControl.getMeteors().size(), (size_t)0);
	
	// Spawns a meteor out of scope and ensures its despawned
    meteorControl.spawnMeteorAt(constants::GAME_WIDTH/2,constants::GAME_HEIGHT+999);
	ASSERT_EQ(meteorControl.getMeteors().size(), (size_t)1);
	
	meteorControl.update(0.1);
	
	ASSERT_EQ(meteorControl.getMeteors().size(), (size_t)0);
}

// Ensures meteors can spawn naturally
TEST_F(MeteorControlTest, update_spawns_meteors){
	ASSERT_EQ(meteorControl.getMeteors().size(), (size_t)0);
    
    // Trys to spawn a lot of meteors
    for(int i=0;i<999;i++){
		meteorControl.update(0.1);		
		if(!meteorControl.getMeteors().empty())
			break;
	}
	
	// Ensures meteors got spawned
	ASSERT_GT(meteorControl.getMeteors().size(), (size_t)0);
}