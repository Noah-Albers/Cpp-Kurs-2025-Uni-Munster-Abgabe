/*
 * PlayerTest.cpp
 *
 *  Created on: 02.08.2025
 *      Author: Noah
 */

#include <gtest/gtest.h>
#include "../../src/model/game/Player.h"
#include "../../src/model/Constants.hpp"
#include "../CommonMockClasses.cpp"
#include <gmock/gmock.h>

// Ensures the constructor sets the correct parameters like
// Position, invulnerability and lives
TEST(PlayerTest, constructor){
    Player player;

    // Position set correctly
    ASSERT_NEAR(player.getPosition().x,constants::GAME_WIDTH/2,0.00001);
    ASSERT_NEAR(player.getPosition().y,constants::GAME_HEIGHT - player.getSprite().getTextureRect().size.y,0.00001);

    // Invulnerability set correctly
    ASSERT_FALSE(player.isInvulnerable());

    // Initial number of lives correct
    ASSERT_EQ(player.getLifes(),constants::PLAYER_START_LIFES);

    // Is not dead
    ASSERT_FALSE(player.isDead());
}

// Ensures that updates doesn't change the "health" state
TEST(PlayerTest, update) {
    Player player;
    player.update(1.0);

    ASSERT_FALSE(player.isInvulnerable());
    ASSERT_EQ(player.getLifes(),constants::PLAYER_START_LIFES);
    ASSERT_FALSE(player.isDead());
}

// Ensures setposition works
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

// Ensures invulnerability works
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
// Ensures setLifes and isDead work
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

// Ensures Player-Draw calls work
TEST(PlayerTest, draw){

    Player player;
    sf::RenderWindow window(sf::VideoMode({10, 10}), "");
	MockLayer layer(window);

    // Ensure the player is being drawn when alive and vulnerable
    EXPECT_CALL(layer, add_to_layer(testing::_))
        .Times(testing::AtLeast(1));

    player.draw(layer);

     ::testing::Mock::VerifyAndClearExpectations(&layer);

    // Ensures the player is not drawn when dead

    player.setLifes(0);

    EXPECT_CALL(layer, add_to_layer(testing::_))
        .Times(0);

    player.draw(layer);
}

// Ensures blinking works
TEST(PlayerTest, blinking){
    Player player;
    sf::RenderWindow window(sf::VideoMode({10, 10}), "");
	MockLayer layer(window);

    // Ensure the player is not drawn when at the first frame of ticking
    float time = (float) constants::PLAYER_BLINK_LENGTH*2/100;
    player.setInvulnerable(time);

    EXPECT_CALL(layer, add_to_layer(testing::_))
        .Times(0);

    player.draw(layer);

    // Ensures the player is drawn when at the second frame of ticking
    float time2 = ((float) (constants::PLAYER_BLINK_LENGTH*1.5))/100.0f ;
    player.setInvulnerable(time2);

    EXPECT_CALL(layer, add_to_layer(testing::_))
        .Times(testing::AtLeast(1));

    player.draw(layer);
}

// Ensures the shieldbar state works
TEST(PlayerTest, shieldbar){
	Player p;
	
	// Should startout with his shild full
	ASSERT_TRUE(p.hasShield());
	
	// Ensures the clamping of the shieldbar works
	p.setShieldbar(0.99);
	ASSERT_NEAR(p.getShieldbar(), 0.99, 0.001);
	ASSERT_FALSE(p.hasShield());
	
	p.setShieldbar(1);
	ASSERT_NEAR(p.getShieldbar(), 1, 0.001);
	ASSERT_TRUE(p.hasShield());
	
	p.setShieldbar(0);
	ASSERT_NEAR(p.getShieldbar(), 0, 0.001);
	ASSERT_FALSE(p.hasShield());
	
	p.setShieldbar(-0.5);
	ASSERT_NEAR(p.getShieldbar(), 0, 0.001);
	ASSERT_FALSE(p.hasShield());
	
	p.setShieldbar(1.2);
	ASSERT_NEAR(p.getShieldbar(), 1, 0.001);
	ASSERT_TRUE(p.hasShield());
}
