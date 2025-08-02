/**
 * LevelControl.cpp
 * created on 28.07
 * author olly
 */

#include "LevelControl.h"
#include "../../model/Constants.hpp"
#include <cmath>
#include "AlienControl.h"
#include "UIControl.h"

LevelControl::LevelControl() :
	currentLevel(-1),
    score(0)
    {}

LevelControl::~LevelControl() {};

void LevelControl::populate(AlienControl* alienControl, UIControl* uiControl) {
    this->alienControl = alienControl;
    this->uiControl = uiControl;
}

void LevelControl::nextLevel() {
	// Ensures no alien still exists (Even tho they shouldn't)
	alienControl->getAliens().clear();
	
	// Increments to the next level
	++currentLevel;
	
	int alienLines = calculateLineAmount();
	int aliensPerLine = calculateAliensPerLine();
	float alienSpeed = calculateAlienSpeed();
   	
   	// Advances the background
   	if(currentLevel > 0)
	   	uiControl->nextBackground();

    // Spawns alien grid
    int y = -constants::SCOREBOARD_HEIGHT - alienLines * constants::ALIEN_SPACE_Y;
    for (int i = 0; i < alienLines; i++) {
        int x = (constants::GAME_WIDTH  - (aliensPerLine * constants::ALIEN_SPACE_X)) / 2;

        for (int j = 0; j < aliensPerLine; j++) {
			// Gives each alien randomly 1 - 3 lifes (more than one life is represented with a shield)
			int lifes = rand() % 5 - 2;
			if(lifes <= 0) lifes = 1;

			alienControl->spawnAlienAt(x,y, lifes, alienSpeed);
			
			x += constants::ALIEN_SPACE_X;
        }
        
        y += constants::ALIEN_SPACE_Y;
    }
}

void LevelControl::update() {
	// Reset the level if there are no more aliens
	if(alienControl->getAliens().empty())
        this->nextLevel();
}

// Creates the calculation methods that all have the same linear-formular
#define MAKE_CALCULATION_METHOD(datatype, methodname, startCount, increaseCount, maxCount)\
	const datatype LevelControl::methodname() const {\
		datatype value = startCount + increaseCount * currentLevel;\
		return value > maxCount ? maxCount : value;\
	}
	
MAKE_CALCULATION_METHOD(int, calculateLineAmount, constants::ALIEN_START_LINE_COUNT, constants::ALIEN_LINE_AMOUNT_INCREASE_PER_LEVEL, constants::MAX_ALIEN_LINE_COUNT);
MAKE_CALCULATION_METHOD(int, calculateAliensPerLine, constants::ALIEN_START_ALIENS_PER_LINE, constants::ALIEN_LINE_INCREASE_PER_LEVEL, constants::MAX_ALIENS_PER_LINE);
MAKE_CALCULATION_METHOD(float, calculateAlienSpeed, constants::ALIEN_START_SPEED, constants::ALIEN_SPEED_INCREASE_PER_LEVEL, constants::MAX_ALIEN_SPEED);
MAKE_CALCULATION_METHOD(int, calculatePointsPerKill, 1, constants::SCORE_MULTIPLIER_INCREASE_PER_LEVEL, INFINITY);

#undef MAKE_CALCULATION_METHOD

void LevelControl::increaseScore(){
	score += calculatePointsPerKill();
    uiControl->displayScore(score);
}


// #region Getters/Setters

const int LevelControl::getCurrentLevel() const { return currentLevel; };

// #endregion
