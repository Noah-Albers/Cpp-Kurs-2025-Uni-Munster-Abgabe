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
	virtual ~LevelControl();

	// Part of setup
	// Its imperative to call this before anything else in this class
    void populate(AlienControl* alien_control, UIControl* ui_control);

	// Updates the level control
    void update();

	// Increments the score and displays it
    void increaseScore();
    
	// Getters/Setters
	const int getCurrentLevel() const;
	const int calculatePointsPerKill() const;
private:
	// Communication with other control's
    AlienControl* alien_control;
    UIControl* ui_control;
	
	// Current level (starting from 0 with as the first level for calculation reasons)
    int current_level;
	
	// Current score that the player has reached    
	int score;

	// Advances to the next level
    virtual void nextLevel();
    
    // Calculates various game settings from the current level
    const int calculateLineAmount() const;
	const int calculateAliensPerLine() const;
	const float calculateAlienSpeed() const;
};

#endif /* SRC_CONTROL_LEVELCONTROL_H_*/