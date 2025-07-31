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


// Mock Classes for Dependencies

class MockPlayer {
public:
    MOCK_METHOD(bool, isDead, (), (const));
};

class MockPlayerControl : public PlayerControl {
public:
    MockPlayerControl(Layer &layer) : PlayerControl(layer) {    };

    //MOCK_METHOD(MockPlayer&, getPlayer, (), ());
    MOCK_METHOD(void, killPlayer, (), ());
};

class MockAlienBulletControl : public AlienBulletControl {
public:
    MockAlienBulletControl(Layer &layer) : AlienBulletControl(layer) {  };

    std::list<AlienBullet> bullets;

    MOCK_METHOD(std::list<AlienBullet>&, getBullets, (), ());
    MOCK_METHOD(void, spawnBulletAt, (int, int), ());
};

// Dummy Layer that does nothing
class DummyLayer : public Layer {
public:
    DummyLayer() : Layer(*createDummyWindow()) {}

    MOCK_METHOD(void, add_to_layer, (const sf::Drawable&), (override));

private:
    static sf::RenderWindow* createDummyWindow() {
        // A shared dummy window so Layer’s constructor can be called safely
        static sf::RenderWindow dummy(sf::VideoMode(), "Dummy");
        return &dummy;
    }
};

// ----------------------------------------
// Test Fixture
// ----------------------------------------

class AlienControlTest : public ::testing::Test {
protected:
    DummyLayer dummyLayer;
    MockAlienBulletControl mockBulletControl;
    MockPlayerControl mockPlayerControl;
    LevelControl levelControl;
    AlienControl alienControl;

    // Backing mock player to return from getPlayer()
    MockPlayer mockPlayer;

    AlienControlTest() : alienControl(dummyLayer), mockBulletControl(dummyLayer), mockPlayerControl(dummyLayer) {
        alienControl.populate(&mockBulletControl, &levelControl, &mockPlayerControl);
        //ON_CALL(mockPlayerControl, getPlayer())
         //   .WillByDefault(ReturnRef(mockPlayer));
    }
};

// ----------------------------------------
// Tests
// ----------------------------------------

/*
// Test that dead aliens are removed during update
TEST_F(AlienControlTest, RemovesDeadAliens) {
    alienControl.spawnAlien(100, 0, 0, 1.0f); // Lifes = 0

    EXPECT_EQ(alienControl.getAliens().size(), 1);
    alienControl.update(0.016f); // simulate frame update
    EXPECT_EQ(alienControl.getAliens().size(), 0);
}



// Test that bullets are not spawned when max bullets reached
TEST_F(AlienControlTest, DoesNotSpawnBulletIfLimitReached) {
    std::list<AlienBullet> maxedBullets(constants::MAX_ALIEN_BULLETS);
    ON_CALL(mockBulletControl, getBullets())
        .WillByDefault(ReturnRef(maxedBullets));

    ON_CALL(mockPlayer, isDead())
        .WillByDefault(Return(false));

    alienControl.spawnAlien(50, 10, 1, 1.0f); // One alien

    EXPECT_CALL(mockBulletControl, spawnBulletAt(_, _)).Times(0);
    alienControl.update(0.016f);
}

// Test that killPlayer is called when alien reaches bottom
TEST_F(AlienControlTest, CallsKillPlayerAtBottom) {
    alienControl.spawnAlien(50, constants::GAME_HEIGHT, 1, 1.0f);

    ON_CALL(mockPlayer, isDead()).WillByDefault(Return(false));
    EXPECT_CALL(mockPlayerControl, killPlayer()).Times(1);

    alienControl.update(0.016f);
}

// Test that direction changes when side is reached
TEST_F(AlienControlTest, ChangesDirectionAtSide) {
    // Spawn alien at right edge to trigger side flag
    alienControl.spawnAlien(constants::GAME_HEIGHT, 50, 1, 1.0f);

    ON_CALL(mockPlayer, isDead()).WillByDefault(Return(false));

    EXPECT_NO_THROW(alienControl.update(0.016f)); // should not crash
}

*/