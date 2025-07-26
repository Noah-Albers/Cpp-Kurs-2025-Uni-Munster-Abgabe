#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "../view/Layer.hpp"
#include "PlayerControl.h"
#include "BulletControl.h"
#include "AlienControl.h"

// Game class
class Game {

public:    
    //initialize the game (window and controls)
    Game();

    // start the game
    void start();
    
    // Singleton access method
    static Game& getInstance();

	// Getters/Setters
	BulletControl& getBulletControl();

private:
	// Singleton to the game instance
    static Game& instance;

    // processes user input, returns true if window has been closed
    bool input();

    // updates all game elements
    void update(float time_passed);

    // draws the scene
    void draw();

    sf::RenderWindow window;

    // view area and layers
    sf::View view;
    Layer game_layer;
    
    // Controllers for the game
    PlayerControl player_control;
    BulletControl bullet_control;
    AlienControl alien_control;
};

#endif