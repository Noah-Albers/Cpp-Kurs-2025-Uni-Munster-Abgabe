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

#include "../../src/control/controls/AlienBulletControl.h"
#include "../../src/control/controls/AlienControl.h"
#include "../../src/control/controls/BulletControl.h"
#include "../../src/control/controls/LevelControl.h"
#include "../../src/control/controls/MeteorControl.h"
#include "../../src/control/controls/ParticleControl.h"
#include "../../src/control/controls/PlayerControl.h"
#include "../../src/control/controls/UIControl.h"

// Mock classes
class UIControlMock : public UIControl {
    public:
    UIControlMock(Layer &layer, Layer &layerbg) : UIControl(layer, layerbg) {};

    MOCK_METHOD(void, displayScore, (int score), (override));
};

class LevelControlMock : public LevelControl {
    public:
    LevelControlMock() : LevelControl() {};
    
    MOCK_METHOD(void, nextLevel, (), (override));
};


// ----------------------------------------
// Test Fixture
// ----------------------------------------

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
    Layer layer;
    Layer layerbg;
    AlienBulletControl  alienBulletControl;
    AlienControl        alienControl;
    BulletControl       bulletControl;
    LevelControl        levelControl;
    MeteorControl       meteorControl;
    ParticleControl     particleControl;
    PlayerControl       playerControl;
    UIControl           uiControl;
};

// Tests

TEST_F(LevelControlTest, UIControlDisplayScoreCall) {
    UIControlMock uiControlMock(layer, layerbg);
    uiControlMock.populate(&playerControl);
    levelControl.populate(&alienControl, &uiControlMock);

    EXPECT_CALL(uiControlMock, displayScore(1))
    	.Times(1);
    levelControl.increaseScore();
}

TEST_F(LevelControlTest, Update) {
    LevelControlMock levelControlMock;
    levelControlMock.populate(&alienControl, &uiControl);
    alienControl.populate(&alienBulletControl, &levelControlMock, &playerControl);

    //Expects only on call, if 0 or 2 test fails
    EXPECT_CALL(levelControlMock, nextLevel())
    	.Times(1);
    levelControlMock.update();

    alienControl.spawnAlien(10, 10, 2, 1.0);
    levelControlMock.update();
}

TEST_F(LevelControlTest, NextLevelSpawnAlien) {
    ASSERT_EQ(alienControl.getAliens().size(), (size_t)0);

    levelControl.update();
    ASSERT_EQ(alienControl.getAliens().size(), (size_t)(constants::ALIEN_START_LIENS_PER_LINE * constants::ALIEN_START_LINE_COUNT));
    alienControl.getAliens().clear();

    levelControl.update();
    ASSERT_EQ(alienControl.getAliens().size(), (size_t)((constants::ALIEN_LINE_INCREASE_PER_LEVEL + constants::ALIEN_START_LIENS_PER_LINE) * (constants::ALIEN_LINE_AMOUNT_INCREASE_PER_LEVEL + constants::ALIEN_START_LINE_COUNT)));
    alienControl.getAliens().clear();

    for (int i = 0; i < 99; i++)
    {
        levelControl.update();
        alienControl.getAliens().clear();
    }
    levelControl.update();
    ASSERT_EQ(alienControl.getAliens().size(), (const long unsigned int)(constants::MAX_ALIEN_LINE_COUNT * constants::MAX_ALIENS_PER_LINE));
}