#include "../../src/control/controls/ParticleControl.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include "../../src/model/Constants.hpp"
#include "../CommonMockClasses.cpp"
#include "../../src/assets/AssetMappings.h"

TEST(ParticleControlTest, spawnParticlesAndDraw){

    sf::RenderWindow window(sf::VideoMode({10, 10}), "");
	MockLayer layer(window);
    ParticleControl particleControl(layer);

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

TEST(ParticleControlTest, update){
    sf::RenderWindow window(sf::VideoMode({10, 10}), "");
	MockLayer layer(window);
    ParticleControl particleControl(layer);

    particleControl.spawnExplosionParticle(10,10);

    particleControl.update(constants::PARTICLE_EXPLOSION_LENGTH/2);

    ASSERT_EQ(particleControl.getParticles().size(),(size_t)1);

    particleControl.update(constants::PARTICLE_EXPLOSION_LENGTH+1);

    ASSERT_TRUE(particleControl.getParticles().empty());



}