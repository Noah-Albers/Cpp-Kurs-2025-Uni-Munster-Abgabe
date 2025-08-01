#include <gtest/gtest.h>
#include "../../src/control/controls/MeteorControl.h"
#include "../../src/model/Constants.hpp"
#include "../MockClasses.cpp"
#include <gmock/gmock.h>


TEST(MeteorControlTest, spawnMeteor){
    sf::RenderWindow window(sf::VideoMode({10, 10}), "");
	  MockLayer layer(window);
    MeteorControl meteorControl(layer);

    meteorControl.spawnMeteorAt(constants::GAME_WIDTH/2,constants::GAME_HEIGHT/2);

    ASSERT_NEAR(meteorControl.getMeteors().front().getPosition().x,constants::GAME_WIDTH/2,0.0001);
    ASSERT_NEAR(meteorControl.getMeteors().front().getPosition().y,constants::GAME_HEIGHT/2- meteorControl.getMeteors().front().getSprite().getLocalBounds().size.y,0.0001);
}

TEST(MeteorControlTest, draw){
    sf::RenderWindow window(sf::VideoMode({10, 10}), "");
	  MockLayer layer(window);
    MeteorControl meteorControl(layer);

    meteorControl.spawnMeteorAt(constants::GAME_WIDTH/2,constants::GAME_HEIGHT/2);
    meteorControl.spawnMeteorAt(constants::GAME_WIDTH,constants::GAME_HEIGHT);
    meteorControl.spawnMeteorAt(0,0);

    EXPECT_CALL(layer, add_to_layer(testing::_))
        .Times(3);
    
    meteorControl.draw();

}

TEST(MeteorControlTest, updateNormally){
    sf::RenderWindow window(sf::VideoMode({10, 10}), "");
	  MockLayer layer(window);
    MeteorControl meteorControl(layer);

    //in the beginning there are no meteors
    meteorControl.update(0);

    ASSERT_TRUE(meteorControl.getMeteors().empty());

    // after the delay time passed, a meteor should be spawned
    meteorControl.update(constants::METEOR_DELAY+1);

    ASSERT_EQ((int)meteorControl.getMeteors().size(),1);



}
/*
TEST(MeteorControlTest, collisionWithPlayer){
  sf::RenderWindow window(sf::VideoMode({10, 10}), "");
	  MockLayer layer(window);
    MeteorControl meteorControl(layer);
    PlayerControl playerControl(layer);
    meteorControl.populate(&playerControl);

    meteorControl.spawnMeteor(constants::GAME_WIDTH/2,constants::GAME_HEIGHT/2);
    playerControl.getPlayer().setPosition(constants::GAME_WIDTH/2,constants::GAME_HEIGHT/2);


    ASSERT_EQ((int)meteorControl.getMeteors().size(),1);


    EXPECT_CALL(playerControl,damagePlayer(testing::_))
        .Times(1);

    meteorControl.update(0);

    ASSERT_TRUE(meteorControl.getMeteors().empty());
    

}*/