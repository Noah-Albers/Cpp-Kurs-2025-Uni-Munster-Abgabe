/**
 * LevelControl.cpp
 * created on 28.07
 * author olly
 */

#include "LevelControl.h"
#include "../model/Constants.hpp"
#include <cmath>
#include "AlienControl.h"

LevelControl::LevelControl() {
    current_level = 0;
    current_score_multiplier = 1;
    count_alien_alive = 0;
}

void LevelControl::populate(AlienControl* AlienControl) {
    this->alien_control = AlienControl;
}

LevelControl::~LevelControl() { }

void LevelControl::nextLevel() {
    // Levelparameter erhöhen
    current_level++;
    current_score_multiplier += constants::SCORE_MULTIPLIER_PER_LEVEL;
    current_alien_speed = ((current_level - 1) * constants::ALIEN_INCREASE_PER_LEVEL) + constants::ALIEN_BASE_SPEED;
    count_alien_total = current_level * constants::ALIEN_INCREASE_PER_LEVEL;

    // Alienanzahl erhöhen
    count_alien_lines = current_level * constants::ALIEN_LINE_INCREASE_PER_LEVEL;
    count_alien_per_line = current_level * constants::ALIEN_INCREASE_PER_LEVEL;
    if (count_alien_per_line > constants::MAX_ALIEN_PER_LINE) {
        count_alien_per_line = constants::MAX_ALIEN_PER_LINE;
    }


    // Alien reihen spawnen
    int y = constants::ALIEN_SPACE_Y;
    for (int i = 0; i < count_alien_lines; i++) {
        int x = (constants::GAME_WIDTH  - (count_alien_per_line * constants::ALIEN_SPACE_X)) / 2;

        for (int j = 0; j < count_alien_per_line; j++) {
            alien_control->spawnAlien(x,y, 1); //TODO: Add random chance for shields
            x = x + constants::ALIEN_SPACE_X;
        }
        y = y + constants::ALIEN_SPACE_Y;
    }

    count_alien_alive = count_alien_lines * count_alien_per_line;
}

void LevelControl::update() {
    if (count_alien_alive == 0) {
        this->nextLevel();
    }
}

void LevelControl::alien_killed() {
    count_alien_alive--;
    if (count_alien_alive < 0) {
        count_alien_alive = 0;
    }
}