#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "../view/Layer.hpp"
#include "controls/ParticleControl.h"
#include "controls/PlayerControl.h"
#include "controls/UIControl.h"
#include "controls/BulletControl.h"
#include "controls/AlienControl.h"
#include "controls/AlienBulletControl.h"
#include "controls/MeteorControl.h"
#include "controls/LevelControl.h"

// Game class
class Game {

public:    
    // initialize the game (window and controls)
    Game();

    // start the game
    void start();

private:
	// Window object
    sf::RenderWindow window;

    // view areas and layers
    sf::View gameView, uiView;
    Layer gameLayer, uiLayer, backgroundLayer;
    
    // Controllers for the game
    PlayerControl* playerControl;
    BulletControl* bulletControl;
    AlienControl* alienControl;
    AlienBulletControl* alienBulletControl;
    MeteorControl* meteorControl;
	ParticleControl* particleControl;
    UIControl* uiControl;
    LevelControl* levelControl;

	// Resets the game into the starting state
	void resetGame();

    // processes user input, returns true if window has been closed
    bool input();

    // updates all game elements
    void update(const float timePassed);

    // draws the scene
    void draw();
    
	// Returns if the game is lost
	const bool isGameOver() const;
};

#endif