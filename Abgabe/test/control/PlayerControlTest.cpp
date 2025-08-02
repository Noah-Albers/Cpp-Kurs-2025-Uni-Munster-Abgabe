
/*
 * PlayerControlTest.cpp
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

#include "../CommonMockClasses.cpp"

class MockPlayerControl : public PlayerControl {
public:
	MockPlayerControl(Layer& layer) : PlayerControl(layer) {}
	
	Player& getModifiablePlayer(){ return player; };
};

class PlayerControlTest : public ::testing::Test {
public:
	PlayerControlTest() :
		win(sf::VideoMode({10, 10}), "Dummy"),
		layer(win), layerbg(win),
		alienBulletControl(layer), alienControl(layer), bulletControl(layer), levelControl(),
		meteorControl(layer), particleControl(layer), playerControl(layer), uiControl(layer, layerbg)
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
	AlienBulletControl alienBulletControl;
	AlienControl alienControl;
	BulletControl bulletControl;
	LevelControl levelControl;
	MeteorControl meteorControl;
	ParticleControl particleControl;
	MockPlayerControl playerControl;
	UIControl uiControl;
};

// Ensures the player's controls work
TEST_F(PlayerControlTest, player_can_move) {
	auto& player = playerControl.getPlayer();
	auto& pos = player.getPosition();
	
	// Simulates movement
	playerControl.keyStateChanged(true, sf::Keyboard::Key::W);
	playerControl.keyStateChanged(true, sf::Keyboard::Key::D);
	playerControl.update(1);

	auto& posNew = player.getPosition();

	// Ensures position has changed
	ASSERT_GE(abs(posNew.x - pos.x),0.1);
	ASSERT_GE(abs(posNew.y - pos.y),0.1);
}

// Ensures low damage removes the shield, damages the player
// ensure invulnerability, does not prevent the player
// from moving
TEST_F(PlayerControlTest, player_damage_low) {
	auto& player = playerControl.getModifiablePlayer();
	
	// Ensures the player has his shield
	ASSERT_TRUE(player.hasShield());
	auto lifes = player.getLifes();
	
	// Simulates small damage
	playerControl.damagePlayer(1);
	
	// Ensures shield got removed but lifes have not changed
	// Ensures player is not invulnerable
	// Ensures player is not dead
	ASSERT_FALSE(player.hasShield());
	ASSERT_EQ(lifes, player.getLifes());
	ASSERT_TRUE(player.isInvulnerable());
	
	player.setInvulnerable(-1);
	
	ASSERT_FALSE(player.isInvulnerable());
	ASSERT_FALSE(player.isDead());
	
	
	// Simulates movement
	playerControl.keyStateChanged(true, sf::Keyboard::Key::W);
	playerControl.keyStateChanged(true, sf::Keyboard::Key::D);
	
	// Simulates low damage
	playerControl.damagePlayer(1);
	
	// Ensures player lifes got decreased, player is invulnerable and not dead
	ASSERT_EQ(lifes-1, player.getLifes());
	ASSERT_TRUE(player.isInvulnerable());
	ASSERT_FALSE(player.isDead());
	
	// Ensures the player's movement has not been impacted
	ASSERT_EQ(player.getVerticalDirection(), VerticalDirection::UP);
	ASSERT_EQ(player.getHorizontalDirection(), HorizontalDirection::RIGHT);
}

// Ensure killPlayer kills the player
// Ensure player can no longer shot when dead
// Ensures can no longer move when dead
TEST_F(PlayerControlTest, player_kill) {
	auto& player = playerControl.getPlayer();
	
	playerControl.keyStateChanged(true, sf::Keyboard::Key::W);
	playerControl.keyStateChanged(true, sf::Keyboard::Key::D);
	
	playerControl.killPlayer();
	
	playerControl.keyStateChanged(true, sf::Keyboard::Key::Space);
	playerControl.update(1);
	
	// Ensures the player is dead
	ASSERT_EQ(player.getLifes(), 0);
	ASSERT_TRUE(player.isDead());
	
	// Ensures the player can't move while dead
	ASSERT_EQ(player.getVerticalDirection(), VerticalDirection::NONE);
	ASSERT_EQ(player.getHorizontalDirection(), HorizontalDirection::NONE);
	
	ASSERT_EQ(bulletControl.getBullets().size(), (size_t)0);
}

// Ensures the shield is handled correctly
TEST_F(PlayerControlTest, shieldbar) {
	auto& player = playerControl.getModifiablePlayer();

	// Ensures shield is present at start
	ASSERT_TRUE(player.hasShield());
	
	// Ensures damage only removes the shield not the lifes
	auto lifes = player.getLifes();	
	playerControl.damagePlayer();
	
	ASSERT_EQ(player.getLifes(), lifes);
	ASSERT_FALSE(player.hasShield());
	
	// Ensures shield regenerates after some time
	playerControl.update(99999);
	
	ASSERT_TRUE(player.hasShield());
}

// Ensures the player can be drawn
// Ensures player is not longer drawn when dead
TEST_F(PlayerControlTest, draw) {

	// Checks that player can be drawn when alive
	EXPECT_CALL(layer, add_to_layer(testing::_))
		.Times(testing::AtLeast(1));

	playerControl.draw();
	
	// Checks that player can not longer be drawn when dead
	playerControl.killPlayer();
	
	EXPECT_CALL(layer, add_to_layer(testing::_))
		.Times(testing::AtLeast(0));
		
	playerControl.draw();
}

