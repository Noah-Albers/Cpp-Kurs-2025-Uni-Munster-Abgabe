/**
 * LevelControl.cpp
 * created on 28.07
 * author olly
 */

#include "LevelControl.h"
#include "../model/Constants.hpp"

LevelControl::LevelControl() {
    current_level = 0;
    current_score_multiplier = 1;
}

LevelControl::~LevelControl() { }

void LevelControl::nextLevel() {
    current_level++;
    current_score_multiplier =+ constants::SCORE_MULTIPLIER_PER_LEVEL;
    current_alien_speed = ((current_level - 1) * constants::ALIEN_INCREASE_PER_LEVEL) + constants::ALIEN_BASE_SPEED;
    count_alien_total = current_level * constants::ALIEN_INCREASE_PER_LEVEL;

    
}

void LevelControl::update() {
    
}