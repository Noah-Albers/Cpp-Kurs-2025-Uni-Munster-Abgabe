/**
 * LevelControl.cpp
 * created on 28.07
 * author olly
 */

#include "LevelControl.h"
#include "../model/Constants.hpp"
#include <cmath>
#include "AlienControl.h"
#include "UIControl.h"

LevelControl::LevelControl() :
	current_level(0),
	count_alien_total(0),
	current_alien_speed(0),
	current_score_multiplier(1) {}

void LevelControl::populate(AlienControl* alien_control, UIControl* ui_control) {
    this->alien_control = alien_control;
    this->ui_control = ui_control;
}

void LevelControl::nextLevel() {
	// Ensures no alien still exists (Even tho they shouldn't)
	alien_control->getAliens().clear();
	
	// Updates to the next level stats
   	nextLevelStats();
   	
   	// Advances the background
   	if(current_level > 1)
	   	ui_control->nextBackground();

    // Spawns alien grid
    int y = -constants::SCOREBOARD_HEIGHT - count_alien_per_line * constants::ALIEN_SPACE_Y;
    for (int i = 0; i < count_alien_lines; i++) {
        int x = (constants::GAME_WIDTH  - (count_alien_per_line * constants::ALIEN_SPACE_X)) / 2;

        for (int j = 0; j < count_alien_per_line; j++) {
			// Gives each alien randomly 1 - 3 lifes (more than one life is represented with a shield)
			int lifes = rand() % 5 - 2;
			if(lifes <= 0) lifes = 1;

			alien_control->spawnAlien(x,y, lifes);
			
			x += constants::ALIEN_SPACE_X;
        }
        
        y += constants::ALIEN_SPACE_Y;
    }
}

void LevelControl::nextLevelStats() {
	 // Advances level parameters
    current_level++;
    current_score_multiplier += constants::SCORE_MULTIPLIER_PER_LEVEL;
    current_alien_speed = ((current_level - 1) * constants::ALIEN_INCREASE_PER_LEVEL) + constants::ALIEN_BASE_SPEED;
    count_alien_total = current_level * constants::ALIEN_INCREASE_PER_LEVEL;

    // Advances total alien amount
    count_alien_lines = current_level * constants::ALIEN_LINE_INCREASE_PER_LEVEL;
    count_alien_per_line = current_level * constants::ALIEN_INCREASE_PER_LEVEL;
    if (count_alien_per_line > constants::MAX_ALIEN_PER_LINE)
        count_alien_per_line = constants::MAX_ALIEN_PER_LINE;
}

void LevelControl::update() {
	// Reset the level if there are no more aliens
	if(alien_control->getAliens().empty())
        this->nextLevel();
}
