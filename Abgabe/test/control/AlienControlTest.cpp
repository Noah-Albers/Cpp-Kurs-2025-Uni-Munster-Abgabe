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

    /*



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