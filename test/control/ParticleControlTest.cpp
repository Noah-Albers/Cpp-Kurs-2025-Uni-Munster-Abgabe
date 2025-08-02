/*
 * ParticleControlTest.cpp
 *
 *  Created on: 01.08.2025
 *      Author: Alice
 */
 
#include <gmock/gmock.h>
#include <gtest/gtest.h>
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


class ParticleControlTest :  public ::testing::Test { 
public:
    ParticleControlTest() :
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

// Ensures particles are spawned from the different spawners
// Ensures these particles are also drawn
TEST_F(ParticleControlTest, spawns_particles_and_draws_them){
    particleControl.spawnExplosionParticle(10,10);

    ASSERT_EQ(particleControl.getParticles().size(),(size_t)1);

    particleControl.spawnPlayerDeathParticle(10,10);

    ASSERT_EQ(particleControl.getParticles().size(),(size_t)2);

    particleControl.spawnMeteorExplosionParticle(10,10);

    ASSERT_EQ(particleControl.getParticles().size(),(size_t)3);

    EXPECT_CALL(layer, add_to_layer(testing::_))
        .Times(3);

    particleControl.draw();
}

// Ensures particles are updated and dead ones are removed
TEST_F(ParticleControlTest, update){
    particleControl.spawnExplosionParticle(10,10);

    particleControl.update(constants::PARTICLE_EXPLOSION_LENGTH/2);

    ASSERT_EQ(particleControl.getParticles().size(),(size_t)1);

    particleControl.update(constants::PARTICLE_EXPLOSION_LENGTH+1);

    ASSERT_TRUE(particleControl.getParticles().empty());
}