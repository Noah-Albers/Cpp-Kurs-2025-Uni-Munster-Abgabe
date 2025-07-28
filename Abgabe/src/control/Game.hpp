#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "../view/Layer.hpp"
#include "ParticleControl.h"
#include "PlayerControl.h"
#include "UIControl.h"
#include "BulletControl.h"
#include "AlienControl.h"
#include "AlienBulletControl.h"
#include "MeteorControl.h"

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
	PlayerControl& getPlayerControl();
    AlienBulletControl& getAlienBulletControl();

	UIControl& getUIControl();
	ParticleControl& getParticleControl();

private:
    // processes user input, returns true if window has been closed
    bool input();

    // updates all game elements
    void update(float time_passed);

    // draws the scene
    void draw();

    sf::RenderWindow window;

    // view areas and layers
    sf::View gameView;
    Layer gameLayer;
    
    // Controllers for the game
    PlayerControl player_control;
    BulletControl bullet_control;
    AlienControl alien_control;
    AlienBulletControl alien_bullet_control;
    MeteorControl meteor_control;
	
	
	ParticleControl particle_control;
    UIControl ui_control;
};

#endif