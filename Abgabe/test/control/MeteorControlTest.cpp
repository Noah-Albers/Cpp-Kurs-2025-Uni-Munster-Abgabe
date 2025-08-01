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

