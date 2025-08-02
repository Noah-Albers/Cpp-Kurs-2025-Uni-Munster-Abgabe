/**
 * LevelControlTest.cpp
 * created on 1.8.
 * autho Olly
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

// Mock classes
class MockUIControl : public UIControl {
public:
    MockUIControl(Layer &layer, Layer &layerbg) : UIControl(layer, layerbg) {};

	MOCK_METHOD(void, nextBackground, (), (override));
    MOCK_METHOD(void, displayScore, (int score), (override));
};

class MockLevelControl : public LevelControl {
public:
    MockLevelControl() : LevelControl() {};
	
	void forwardNextLevel() { nextLevel(); };
	int forwardGetScore() { return score; };
};

class LevelControlTest :  public ::testing::Test { 
    public:
    LevelControlTest() :
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
    MockLevelControl	levelControl;
    MeteorControl       meteorControl;
    ParticleControl     particleControl;
    PlayerControl       playerControl;
    MockUIControl           uiControl;
};

// Ensures that old aliens are removed when a new level is started
TEST_F(LevelControlTest, nextLvl_removes_aliens) {
	for(int i=0;i<999;i++)
		alienControl.spawnAlien(10,10, 1, 1.0);

	ASSERT_EQ(alienControl.getAliens().size(), (size_t)999);

	levelControl.forwardNextLevel();
	
	ASSERT_LE(alienControl.getAliens().size(), (size_t)900);
}

// Ensures level is increased when a new level is started
TEST_F(LevelControlTest, nextLvl_increase_lvl) {
	auto lvl = levelControl.getCurrentLevel();

	levelControl.forwardNextLevel();
	
	ASSERT_EQ(levelControl.getCurrentLevel(), lvl+1);
}

// Ensures the next background is selected when the level is increased the second time
TEST_F(LevelControlTest, nextLvl_increase_background) {
	EXPECT_CALL(uiControl, nextBackground())
		.Times(1);

	levelControl.forwardNextLevel();
	levelControl.forwardNextLevel();
}

// Ensures new Aliens are spawned
TEST_F(LevelControlTest, nextLvl_spawns_aliens) {
	// Ensures that level increases spawn aliens
	for(int i=0;i<10;i++){
		// Ensures clean alien list
		alienControl.getAliens().clear();
		levelControl.forwardNextLevel();
		
		// Ensures aliens have been spawned
		ASSERT_GT(alienControl.getAliens().size(), (size_t)0);
	}
}

// Ensures update updates the level only when no aliens are present
TEST_F(LevelControlTest, update_advances_level) {	
	
	// Ensures the first level is skipped to prevent some annoying
	// none-increment for the first level
	levelControl.forwardNextLevel();
	
	// Checks this for the first few levels
	for(int i=0;i<10;i++){
		// Ensures no level is advances if aliens exist
		alienControl.spawnAlien(10,10, 1, 1.0);
		levelControl.update();

		ASSERT_EQ(levelControl.getCurrentLevel(), i);

		// Ensures the level is advances if aliens exist
		alienControl.getAliens().clear();
		levelControl.update();
		ASSERT_EQ(levelControl.getCurrentLevel(),i+1);
	}
}

// Ensures that increase score works
TEST_F(LevelControlTest, increaseScore) {
    auto score = levelControl.forwardGetScore();
    
    EXPECT_CALL(uiControl, displayScore(1))
    	.Times(1);
    levelControl.increaseScore();
    
    ASSERT_EQ(levelControl.forwardGetScore(), score+1);
}