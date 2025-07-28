/*
LevelControl.h
created on 28.07
author olly
*/

#ifndef SRC_CONTROL_LEVELCONTROL_H_
#define SRC_CONTROL_LEVELCONTROL_H_


class LevelControl
{
private:
    int current_level;
    int count_alien_alive;
    int count_alien_total;
    int count_alien_per_line;

    float current_alien_speed;
    int current_score_multiplier;

    void nextLevel();
public:
    LevelControl();
    virtual ~LevelControl();

    void update();
};

#endif /* SRC_CONTROL_LEVELCONTROL_H_*/