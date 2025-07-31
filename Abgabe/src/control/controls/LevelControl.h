/*
LevelControl.h
created on 28.07
author olly
*/

#ifndef SRC_CONTROL_LEVELCONTROL_H_
#define SRC_CONTROL_LEVELCONTROL_H_


// Declares classes to avoid circular dependencies
class AlienControl;
class UIControl;
class Alien;

class LevelControl
{
public:
    LevelControl();

	// Part of setup
	// Its imperative to call this before anything else in this class
    void populate(AlienControl* alien_control, UIControl* ui_control);

	// Updates the level control
    void update();


    void increaseScore();

private:
	// Communication with other control's
    AlienControl* alien_control;
    UIControl* ui_control;
	
	// Stats of the current level
    int current_level;
    int count_alien_total;
    int count_alien_per_line;
    int count_alien_lines;
    
	int score;

    float current_alien_speed;
    int current_score_multiplier;

	// Advances to the next level
    void nextLevel();
    
    // Calculates the stats for the next level
    void nextLevelStats();

};

#endif /* SRC_CONTROL_LEVELCONTROL_H_*/