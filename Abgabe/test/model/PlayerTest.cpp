#include <gtest/gtest.h>
#include "../../src/model/game/Player.h"
#include "../../src/model/Constants.hpp"




TEST(PlayerTest, constructor){
    Player player;

    //position set correctly
    ASSERT_NEAR(player.getPosition().x,constants::GAME_WIDTH/2,0.00001);
    ASSERT_NEAR(player.getPosition().y,constants::GAME_HEIGHT - player.getSprite().getTextureRect().size.y,0.00001);

    //invulnerability set correctly
    ASSERT_FALSE(player.isInvulnerable());

    ASSERT_EQ(player.getLifes(),constants::PLAYER_START_LIFES);

    ASSERT_FALSE(player.isDead());
}

TEST(PlayerTest, update){
    Player player;
    player.update(1.0);

    ASSERT_FALSE(player.isInvulnerable());

    ASSERT_EQ(player.getLifes(),constants::PLAYER_START_LIFES);

    ASSERT_FALSE(player.isDead());

}

TEST(PlayerTest, setPosition){
    Player player;
    player.setPosition(sf::Vector2f(constants::GAME_WIDTH/2,constants::GAME_HEIGHT/2));

    ASSERT_NEAR(player.getPosition().x,(float)constants::GAME_WIDTH/2,0.00001);
    ASSERT_NEAR(player.getPosition().y,(float)constants::GAME_HEIGHT/2,0.00001);

    player.setPosition(sf::Vector2f(-100,-100));

    ASSERT_NEAR(player.getPosition().x,0,0.00001);
    ASSERT_NEAR(player.getPosition().y,0,0.00001);

    player.setPosition(sf::Vector2f(constants::GAME_WIDTH+100,constants::GAME_HEIGHT+100));

    ASSERT_NEAR(player.getPosition().x,(float)constants::GAME_WIDTH,0.00001);
    ASSERT_NEAR(player.getPosition().y,(float)constants::GAME_HEIGHT,0.00001);

    player.setPosition(sf::Vector2f(constants::GAME_WIDTH/2,constants::GAME_HEIGHT+100));

    ASSERT_NEAR(player.getPosition().x,(float)constants::GAME_WIDTH/2,0.00001);
    ASSERT_NEAR(player.getPosition().y,(float)constants::GAME_HEIGHT,0.00001);

    player.setPosition(sf::Vector2f(constants::GAME_WIDTH+100,-100));

    ASSERT_NEAR(player.getPosition().x,(float)constants::GAME_WIDTH,0.00001);
    ASSERT_NEAR(player.getPosition().y,0,0.00001);


}


TEST(PlayerTest, invulnarability){
    Player player;
    player.setInvulnerable(3.0);

    ASSERT_TRUE(player.isInvulnerable());

    player.update(1.0);

    ASSERT_TRUE(player.isInvulnerable());

    player.update(2.0);


    ASSERT_TRUE(player.isInvulnerable());

    player.update(2.0);

    ASSERT_FALSE(player.isInvulnerable());

}

TEST(PlayerTest, lifes){
    Player player;

    player.setLifes(3);

    ASSERT_EQ(player.getLifes(),3);

    //lives negative
    player.setLifes(-2);

    ASSERT_EQ(player.getLifes(),0);

    ASSERT_TRUE(player.isDead());

    //lives greater that max lives
    player.setLifes(constants::PLAYER_START_LIFES+3);

    ASSERT_EQ(player.getLifes(),constants::PLAYER_START_LIFES);


}

class MockLayer : public Layer{
    MockLayer
}

TEST(PlayerTest, draw){

    Player player;



    player.setLifes(0);

    //player.draw();

}