#include <gtest/gtest.h>
#include "../../src/model/game/Player.h"
#include "../../src/model/Constants.hpp"
#include "../CommonMockClasses.cpp"
#include <gmock/gmock.h>



TEST(PlayerTest, constructor){
    Player player;

    //position set correctly
    ASSERT_NEAR(player.getPosition().x,constants::GAME_WIDTH/2,0.00001);
    ASSERT_NEAR(player.getPosition().y,constants::GAME_HEIGHT - player.getSprite().getTextureRect().size.y,0.00001);

    //invulnerability set correctly
    ASSERT_FALSE(player.isInvulnerable());

    //initial number of lives correct
    ASSERT_EQ(player.getLifes(),constants::PLAYER_START_LIFES);

    //is not dead
    ASSERT_FALSE(player.isDead());
}

TEST(PlayerTest, update){
    Player player;
    player.update(1.0);

    // when updated and nothing happens, everything should stay the same
    ASSERT_FALSE(player.isInvulnerable());

    ASSERT_EQ(player.getLifes(),constants::PLAYER_START_LIFES);

    ASSERT_FALSE(player.isDead());


}

TEST(PlayerTest, setPosition){
    Player player;
    // player must not leave the game field/screen

    // Player is in the middle of the field
    player.setPosition(sf::Vector2f(constants::GAME_WIDTH/2,constants::GAME_HEIGHT/2));

    ASSERT_NEAR(player.getPosition().x,(float)constants::GAME_WIDTH/2,0.00001);
    ASSERT_NEAR(player.getPosition().y,(float)constants::GAME_HEIGHT/2,0.00001);

    // player is out of the field to the top left
    player.setPosition(sf::Vector2f(-100,-100));

    ASSERT_NEAR(player.getPosition().x,0,0.00001);
    ASSERT_NEAR(player.getPosition().y,0,0.00001);

    // player is out of the field to the bottom right
    player.setPosition(sf::Vector2f(constants::GAME_WIDTH+100,constants::GAME_HEIGHT+100));

    ASSERT_NEAR(player.getPosition().x,(float)constants::GAME_WIDTH,0.00001);
    ASSERT_NEAR(player.getPosition().y,(float)constants::GAME_HEIGHT,0.00001);

    // player is out of the field to the bottom
    player.setPosition(sf::Vector2f(constants::GAME_WIDTH/2,constants::GAME_HEIGHT+100));

    ASSERT_NEAR(player.getPosition().x,(float)constants::GAME_WIDTH/2,0.00001);
    ASSERT_NEAR(player.getPosition().y,(float)constants::GAME_HEIGHT,0.00001);

    // player is out of the field to the top right
    player.setPosition(sf::Vector2f(constants::GAME_WIDTH+100,-100));

    ASSERT_NEAR(player.getPosition().x,(float)constants::GAME_WIDTH,0.00001);
    ASSERT_NEAR(player.getPosition().y,0,0.00001);


}


TEST(PlayerTest, invulnarability){
    Player player;
    //player is invulberable for 3 sec
    player.setInvulnerable(3.0);

    ASSERT_TRUE(player.isInvulnerable());

    // player should still be invulberable after 1 sec and 3 sec
    player.update(1.0);

    ASSERT_TRUE(player.isInvulnerable());

    player.update(2.0);

    ASSERT_TRUE(player.isInvulnerable());

    // Invulnerabilty should have ended after more than 3 sec
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


TEST(PlayerTest, draw){

    Player player;
    sf::RenderWindow window(sf::VideoMode({10, 10}), "");
	MockLayer layer(window);

    //player is being drawn when alive and vulnerable
    EXPECT_CALL(layer, add_to_layer(testing::_))
        .Times(1);

    player.draw(layer);

     ::testing::Mock::VerifyAndClearExpectations(&layer);

    // player is not drawn when dead

    player.setLifes(0);

    EXPECT_CALL(layer, add_to_layer(testing::_))
        .Times(0);

    player.draw(layer);
    

    

}


TEST(PlayerTest, blinking){

   


    Player player;
    sf::RenderWindow window(sf::VideoMode({10, 10}), "");
	MockLayer layer(window);

    //when not drawn
    float time = (float) constants::PLAYER_BLINK_LENGTH*2/100;
    player.setInvulnerable(time);

    EXPECT_CALL(layer, add_to_layer(testing::_))
        .Times(0);

    player.draw(layer);

    // when drawn
    float time2 = ((float) (constants::PLAYER_BLINK_LENGTH*1.5))/100.0f ;
    player.setInvulnerable(time2);

    EXPECT_CALL(layer, add_to_layer(testing::_))
        .Times(1);

    player.draw(layer);

}
