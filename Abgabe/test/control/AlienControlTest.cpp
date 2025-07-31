/**
 * AlienControlTest.cpp
 * Created on 31.07
 * author Olly
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/View.hpp> 

#include "../../src/control/controls/AlienControl.h"
#include "../../src/model/Constants.hpp"


using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::_;



// Dummy Layer that does nothing
class DummyLayer : public Layer {
public:
    DummyLayer() : Layer(*createDummyWindow()) {}

    //MOCK_METHOD(void, add_to_layer, (const sf::Drawable&), (override));

private:
    static sf::RenderWindow* createDummyWindow() {
        // A shared dummy window so Layer’s constructor can be called safely
        static sf::RenderWindow dummy(sf::VideoMode({10, 10}), "Dummy");
        return &dummy;
    }
};

class AlienControlMock : public AlienControl {
public:
    AlienControlMock(Layer &layer) : AlienControl(layer) {  };

    bool forwardAreAliensInGamefield() {
        return this->areAliensInGamefield();
    }
};

// ----------------------------------------
// Test Fixture
// ----------------------------------------

class AlienControlTest : public ::testing::Test {
protected:
    DummyLayer dummyLayer;
    AlienBulletControl alienBulletControl;
    PlayerControl playerControl;
    LevelControl levelControl;
    AlienControlMock alienControl;


    AlienControlTest() : alienBulletControl(dummyLayer), playerControl(dummyLayer), alienControl(dummyLayer) {
        alienControl.populate(&alienBulletControl, &levelControl, &playerControl);
    }
};

// ----------------------------------------
// Tests
// ----------------------------------------
TEST_F(AlienControlTest, SpawnAlien) {
    ASSERT_EQ(alienControl.getAliens().size(), 0);
    
    alienControl.spawnAlien(10, 10, 2, 1.0);
    ASSERT_EQ(alienControl.getAliens().size(), 1);

    alienControl.spawnAlien(12, 12, 1, 1.0);
    ASSERT_EQ(alienControl.getAliens().size(), 2);
}

TEST_F(AlienControlTest, AreAliensInGameField) {
    alienControl.spawnAlien(100,100, 1, 1.0);
    EXPECT_TRUE(alienControl.forwardAreAliensInGamefield());

    alienControl.spawnAlien(100, 0, 1, 1.0);
    EXPECT_TRUE(alienControl.forwardAreAliensInGamefield());

    alienControl.spawnAlien(100, -30, 1, 1.0);
    EXPECT_FALSE(alienControl.forwardAreAliensInGamefield());
}


// Test that dead aliens are removed during update
TEST_F(AlienControlTest, RemovesDeadAliens) {
    alienControl.spawnAlien(100, 0, 0, 1.0);
    EXPECT_EQ(alienControl.getAliens().size(), 1);
    alienControl.update(0.1); // simulate frame update
    EXPECT_EQ(alienControl.getAliens().size(), 0);

    alienControl.spawnAlien(100, 100, 1, 1.0);
    alienControl.spawnAlien(200,200, 0, 1.0);
    EXPECT_EQ(alienControl.getAliens().size(), 2);
    alienControl.update(0.1);
    EXPECT_EQ(alienControl.getAliens().size(), 1);
}

// Test Alien spawn animation
TEST_F(AlienControlTest, AlienSpawnMovement) {
    alienControl.spawnAlien(100, -5, 1, 1.0);
    auto posA = alienControl.getAliens().front().getPosition();

    alienControl.update(0.1);
    auto posB = alienControl.getAliens().front().getPosition();

    ASSERT_NEAR(posA.x, posB.x, 0.000001);
    ASSERT_LE(posA.y, posB.y);
} 

// Test Alien movement
TEST_F(AlienControlTest, AlienNormalMovement) {
    alienControl.spawnAlien(constants::GAME_WIDTH - 1, 100, 1, 1.0);
    auto posA = alienControl.getAliens().front().getPosition();
    auto dirA = alienControl.getAliens().front().getHorizontalDirection();

    alienControl.update(0.5);
    auto posB = alienControl.getAliens().front().getPosition();
    auto dirB = alienControl.getAliens().front().getHorizontalDirection();

    alienControl.update(0.5);
    auto posC = alienControl.getAliens().front().getPosition();

    EXPECT_NE(dirA, dirB);
    //EXPECT_LT(posA.y, posB.y);
    EXPECT_LT(posB.y, posC.y);
    EXPECT_GT(posB.x, posC.x);
}

// No downward move when Player is dead
TEST_F(AlienControlTest, AlienDeadPlayerMovement) {
    playerControl.killPlayer();
    alienControl.spawnAlien(constants::GAME_WIDTH - 1, 100, 1, 1.0);
    auto posA = alienControl.getAliens().front().getPosition();
    auto dirA = alienControl.getAliens().front().getHorizontalDirection();

    alienControl.update(0.5);
    auto posB = alienControl.getAliens().front().getPosition();
    auto dirB = alienControl.getAliens().front().getHorizontalDirection();

    alienControl.update(0.5);
    auto posC = alienControl.getAliens().front().getPosition();

    EXPECT_NE(dirA, dirB);
    EXPECT_NEAR(posA.y, posB.y, 0.000001);
    EXPECT_NEAR(posB.y, posC.y, 0.000001);
    EXPECT_GT(posB.x, posC.x);
}

// TODO: Mock Killplayer if y= 0