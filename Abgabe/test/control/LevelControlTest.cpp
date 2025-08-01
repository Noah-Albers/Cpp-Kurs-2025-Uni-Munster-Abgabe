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

    EXPECT_CALL(uiControlMock, displayScore(1));
    levelControl.increaseScore();
}