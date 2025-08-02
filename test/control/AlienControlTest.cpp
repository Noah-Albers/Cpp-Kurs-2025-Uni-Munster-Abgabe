/**
 * AlienControlTest.cpp
 * Created on 31.07
 * author Olly
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


class MockAlienControl : public AlienControl {
public:
    MockAlienControl(Layer &layer) : AlienControl(layer) {  };

    bool forwardAreAliensInGamefield() { return areAliensInGamefield(); };
};

class AlienControlTest :  public ::testing::Test { 
    public:
    AlienControlTest() :
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
    MockAlienControl    alienControl;
    BulletControl       bulletControl;
    LevelControl        levelControl;
    MeteorControl       meteorControl;
    ParticleControl     particleControl;
    PlayerControl       playerControl;
    UIControl           uiControl;
};

// Ensures that for each alien the sprite is drawn and if it has a shield, that is also drawn
TEST_F(AlienControlTest, draw) {
	// Spawns a few aliens
	alienControl.spawnAlienAt(10,10, 1, 0); // 1 life => no shield
	alienControl.spawnAlienAt(10,10, 2, 0); // 2 lifes => shield
	alienControl.spawnAlienAt(10,10, 3, 0); // 3 lifes => shield
	
	EXPECT_CALL(layer, add_to_layer(testing::_))
		.Times(5);
	
	alienControl.draw();	
}

// Ensures that aliens can spawn
TEST_F(AlienControlTest, spawnAlien) {
    ASSERT_EQ(alienControl.getAliens().size(), (size_t)0);
    
    alienControl.spawnAlienAt(10, 10, 2, 1.0);
    ASSERT_EQ(alienControl.getAliens().size(), (size_t)1);

    alienControl.spawnAlienAt(12, 12, 1, 1.0);
    ASSERT_EQ(alienControl.getAliens().size(), (size_t)2);
}


// Ensures that the test to check that aliens are in the game field works
TEST_F(AlienControlTest, AreAliensInGameField) {
    alienControl.spawnAlienAt(100,100, 1, 1.0);
    EXPECT_TRUE(alienControl.forwardAreAliensInGamefield());

    alienControl.spawnAlienAt(100, 0, 1, 1.0);
    EXPECT_TRUE(alienControl.forwardAreAliensInGamefield());

    alienControl.spawnAlienAt(100, -30, 1, 1.0);
    EXPECT_FALSE(alienControl.forwardAreAliensInGamefield());
}

// Checks if the aliens move into the field when spawning outside
// Also ensures they dont move in the horizontal while doing so
TEST_F(AlienControlTest, update_spawn_moveIntoField) {
    ASSERT_EQ(alienControl.getAliens().size(), (size_t)0);
    
    // Spawn alien
	alienControl.spawnAlienAt(10,-30,1, 1.0);
	
	const Alien& alien = alienControl.getAliens().front();
	
	auto& posA = alien.getPosition();

	// Simulate frame ticks
	alienControl.update(0.5);
	
	auto& posB = alien.getPosition();
	
	// Ensures vertical downward movement and no horizontal movement
	ASSERT_NEAR(posA.x, posB.x, 0.0001);
	ASSERT_LE(posA.y + 0.2, posB.y);
}

// Ensures dead aliens are removed while in the spawning phase
TEST_F(AlienControlTest, update_remove_aliens_afterSpawning) {
    ASSERT_EQ(alienControl.getAliens().size(), (size_t)0);
	
    // Spawn alien (Outside of the game field)
	alienControl.spawnAlienAt(10,-30,1, 1.0);
	Alien& alien = alienControl.getAliens().front();
	
    ASSERT_EQ(alienControl.getAliens().size(), (size_t)1);
    EXPECT_FALSE(alienControl.forwardAreAliensInGamefield());
	
	// Kill it
	alien.removeLife();
	
	// Simulate frame
	alienControl.update(0.5);
	
	// Ensure its removed
    ASSERT_EQ(alienControl.getAliens().size(), (size_t)0);
}

// Ensure dead aliens are removed while in the normal game phase
TEST_F(AlienControlTest, update_remove_aliens_whenSpawning) {
    ASSERT_EQ(alienControl.getAliens().size(), (size_t)0);
	
    // Spawn alien (Inside the game field)
	alienControl.spawnAlienAt(10,10,1, 1.0);
	Alien& alien = alienControl.getAliens().front();
	
    ASSERT_EQ(alienControl.getAliens().size(), (size_t)1);
    EXPECT_TRUE(alienControl.forwardAreAliensInGamefield());
	
	// Kill it
	alien.removeLife();
	
	// Simulate frame
	alienControl.update(0.5);
	
	// Ensure its removed
    ASSERT_EQ(alienControl.getAliens().size(), (size_t)0);
}

// Ensures aliens can randomly shoot bullets
TEST_F(AlienControlTest, update_alien_can_randomly_shot) {
	// Spawns an alien (With no speed to only check shoot ability)
	alienControl.spawnAlienAt(10,10,1, 0);
	
	// Simulates frame to ensure its not dead
	alienControl.update(0.5);
    ASSERT_EQ(alienControl.getAliens().size(), (size_t)1);
	
	// Tries for a long time to check if it can shoot (Usually will only take a few attempts)
	// This might fail once in a blue moon tho
	int tryCtr = 9999;
	while(
			alienBulletControl.getBullets().size() <= 0
		&& 	tryCtr >= 0
		&&	alienControl.getAliens().size() >= 1
	){
		alienControl.update(0.1);
		--tryCtr;
    }
	// Ensures the alien didn't get removed
    ASSERT_EQ(alienControl.getAliens().size(), (size_t)1);
	
	// Ensures the try counter has not burned out
	ASSERT_NE(tryCtr, -1);
    ASSERT_EQ(alienBulletControl.getBullets().size(), (size_t)1);
}

// Ensures aliens can turn the whole grid when one reaches the side
// and they don't move down while doing so
// Ensures they will go down afterwards
TEST_F(AlienControlTest, update_aliens_can_turn) {
	auto& ls = alienControl.getAliens();

	// Spawns a few aliens
	for(int i=0;i<3;i++)
		alienControl.spawnAlienAt(10 + i*5,10,1,1.0);
	
	// Ensures there are 3 aliens and they all are inside the game field
    ASSERT_EQ(ls.size(), (size_t)3);
    EXPECT_TRUE(alienControl.forwardAreAliensInGamefield());
	
	// Ensures they all have the same direction
	auto dir = ls.front().getHorizontalDirection();
	auto yCoord = ls.front().getPosition().y;
	
	for(auto it = ls.begin(); it != ls.end(); ++it)
		ASSERT_EQ(dir, it->getHorizontalDirection());
	
	// Updates them until their direction changes
	int tryCtr = 9999;
	while(ls.front().getHorizontalDirection() == dir){
		// Ensures they all still have that direction	
		for(auto it = ls.begin(); it != ls.end(); ++it)
			ASSERT_EQ(dir, it->getHorizontalDirection());
		
		alienControl.update(0.1);
		--tryCtr;
    }
	// Ensures the try counter has not burned out
	ASSERT_NE(tryCtr, -1);
	
	auto newDir = ls.front().getHorizontalDirection();
	
	// Ensures they all have changed their direction
	// Ensures they didn't move down
	for(auto it = ls.begin(); it != ls.end(); ++it){
		ASSERT_EQ(newDir, it->getHorizontalDirection());
		
		ASSERT_NEAR(it->getPosition().y, yCoord, 0.001);
	}
	
	// Simulates a few more updates
	for(int i=0;i<5;i++)
		alienControl.update(0.1);
	
	// Ensures they will go down now
	for(auto it = ls.begin(); it != ls.end(); ++it)
		ASSERT_GE(it->getPosition().y, yCoord+0.1);
}

// Ensures the player is killed when the aliens reach the bottom
TEST_F(AlienControlTest, update_kills_player_when_aliens_reach_bottom) {
	ASSERT_FALSE(playerControl.getPlayer().isDead());
	ASSERT_TRUE(playerControl.getPlayer().hasShield());
	
	alienControl.spawnAlienAt(100, constants::GAME_HEIGHT, 2, 1.0);
    alienControl.update(0.5);
    
    ASSERT_TRUE(playerControl.getPlayer().isDead());
}

// Ensures no downward movement when the player is dead
TEST_F(AlienControlTest, update_no_downmovement_when_player_is_dead) {
	// Spawns an alien and kills the player
    alienControl.spawnAlienAt(constants::GAME_WIDTH/2, 100, 1, 1.0);
    auto posA = alienControl.getAliens().front().getPosition();
        
    playerControl.killPlayer();

	// Simulates a lot of movement
	for(int i=0;i<200;i++) alienControl.update(0.5);

    auto posB = alienControl.getAliens().front().getPosition();

	// Ensures the aliens have not moved down
    ASSERT_NEAR(posA.y, posB.y, 0.000001);
}
