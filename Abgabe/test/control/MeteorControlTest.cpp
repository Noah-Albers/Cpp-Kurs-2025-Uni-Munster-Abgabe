#include "../../src/control/controls/PlayerControl.h"
#include "../../src/control/controls/BulletControl.h"
#include "../../src/control/controls/ParticleControl.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <iostream>
#include "../../src/control/controls/AlienBulletControl.h"
#include "../../src/control/controls/AlienControl.h"
#include "../../src/control/controls/BulletControl.h"
#include "../../src/control/controls/LevelControl.h"
#include "../../src/control/controls/MeteorControl.h"
#include "../../src/control/controls/ParticleControl.h"
#include "../../src/control/controls/PlayerControl.h"
#include "../../src/control/controls/UIControl.h"
#include "../../src/model/Constants.hpp"
#include "../CommonMockClasses.cpp"


class MeteorControlTest :  public ::testing::Test { 
    public:
    MeteorControlTest() :
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
    LevelControl        levelControl;
    MeteorControl       meteorControl;
    ParticleControl     particleControl;
    PlayerControl       playerControl;
    UIControl           uiControl;
};



TEST_F(MeteorControlTest, spawnMeteor){
    


    meteorControl.spawnMeteorAt(constants::GAME_WIDTH/2,constants::GAME_HEIGHT/2);

    ASSERT_NEAR(meteorControl.getMeteors().front().getPosition().x,constants::GAME_WIDTH/2,0.0001);
    ASSERT_NEAR(meteorControl.getMeteors().front().getPosition().y,constants::GAME_HEIGHT/2- meteorControl.getMeteors().front().getSprite().getLocalBounds().size.y,0.0001);
}

TEST_F(MeteorControlTest, draw){
    

    meteorControl.spawnMeteorAt(constants::GAME_WIDTH/2,constants::GAME_HEIGHT/2);
    meteorControl.spawnMeteorAt(constants::GAME_WIDTH,constants::GAME_HEIGHT);
    meteorControl.spawnMeteorAt(0,0);

    EXPECT_CALL(layer, add_to_layer(testing::_))
        .Times(3);
    
    meteorControl.draw();

}

TEST_F(MeteorControlTest, updateNormally){
    
    //in the beginning there are no meteors
    meteorControl.update(0);

    ASSERT_TRUE(meteorControl.getMeteors().empty());

    // after the delay time passed, a meteor should be spawned
    meteorControl.update(constants::METEOR_DELAY+1);

    ASSERT_EQ((int)meteorControl.getMeteors().size(),1);



}





TEST_F(MeteorControlTest, collisionWithPlayer){
    
    meteorControl.spawnMeteorAt(playerControl.getPlayer().getPosition().x,playerControl.getPlayer().getPosition().y);
    


    ASSERT_EQ((int)meteorControl.getMeteors().size(),1);



    meteorControl.update(0);

    ASSERT_EQ(playerControl.getPlayer().getLifes(),constants::PLAYER_START_LIFES-1);

    ASSERT_TRUE(meteorControl.getMeteors().empty());
    

}

TEST_F(MeteorControlTest, outOfScope){

    meteorControl.spawnMeteorAt(constants::GAME_WIDTH/2,constants::GAME_HEIGHT+19);

    ASSERT_EQ((int)meteorControl.getMeteors().size(),1);

    meteorControl.update(constants::METEOR_DELAY/2);

    ASSERT_TRUE(meteorControl.getMeteors().empty());
}