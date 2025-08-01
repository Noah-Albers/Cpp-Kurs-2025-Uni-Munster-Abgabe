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
	current_level(-1),
    score(0)
    {}

LevelControl::~LevelControl() {};

void LevelControl::populate(AlienControl* alien_control, UIControl* ui_control) {
    this->alien_control = alien_control;
    this->ui_control = ui_control;
}

void LevelControl::nextLevel() {
	// Ensures no alien still exists (Even tho they shouldn't)
	alien_control->getAliens().clear();
	
	// Increments to the next level
	++current_level;
	
	int alienLines = calculateLineAmount();
	int aliensPerLine = calculateAliensPerLine();
	float alienSpeed = calculateAlienSpeed();
   	
   	// Advances the background
   	if(current_level > 0)
	   	ui_control->nextBackground();

    // Spawns alien grid
    int y = -constants::SCOREBOARD_HEIGHT - alienLines * constants::ALIEN_SPACE_Y;
    for (int i = 0; i < alienLines; i++) {
        int x = (constants::GAME_WIDTH  - (aliensPerLine * constants::ALIEN_SPACE_X)) / 2;

        for (int j = 0; j < aliensPerLine; j++) {
			// Gives each alien randomly 1 - 3 lifes (more than one life is represented with a shield)
			int lifes = rand() % 5 - 2;
			if(lifes <= 0) lifes = 1;

			alien_control->spawnAlien(x,y, lifes, alienSpeed);
			
			x += constants::ALIEN_SPACE_X;
        }
        
        y += constants::ALIEN_SPACE_Y;
    }
}

void LevelControl::update() {
	// Reset the level if there are no more aliens
	if(alien_control->getAliens().empty())
        this->nextLevel();
}


// Creates the calculation methods that all have the same linear-formular
#define MAKE_CALCULATION_METHOD(datatype, methodname, start_count, increase_count, max_count)\
	const datatype LevelControl::methodname() const {\
		datatype value = start_count + increase_count * current_level;\
		return value > max_count ? max_count : value;\
	}
	
MAKE_CALCULATION_METHOD(int, calculateLineAmount, constants::ALIEN_START_LINE_COUNT, constants::ALIEN_LINE_AMOUNT_INCREASE_PER_LEVEL, constants::MAX_ALIEN_LINE_COUNT);
MAKE_CALCULATION_METHOD(int, calculateAliensPerLine, constants::ALIEN_START_LIENS_PER_LINE, constants::ALIEN_LINE_INCREASE_PER_LEVEL, constants::MAX_ALIENS_PER_LINE);
MAKE_CALCULATION_METHOD(float, calculateAlienSpeed, constants::ALIEN_START_SPEED, constants::ALIEN_SPEED_INCREASE_PER_LEVEL, constants::MAX_ALIEN_SPEED);
MAKE_CALCULATION_METHOD(int, calculatePointsPerKill, 1, constants::SCORE_MULTIPLIER_INCREASE_PER_LEVEL, INFINITY);

#undef MAKE_CALCULATION_METHOD

void LevelControl::increaseScore(){
    ui_control->displayScore(++score);
}
