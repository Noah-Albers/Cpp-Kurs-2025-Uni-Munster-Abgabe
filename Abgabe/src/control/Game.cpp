#include "Game.hpp"

#include <SFML/Window/Keyboard.hpp>

#include "../model/Constants.hpp"
#include "UIControl.h"
#include "BulletControl.h"
#include "PlayerControl.h"
#include "AlienControl.h"

// Initialize the singleton

 Game& Game::getInstance() {
	static Game instance;
    return instance;
}

Game::Game() :
	window(sf::VideoMode({constants::GAME_WIDTH, constants::GAME_HEIGHT + constants::SCOREBOARD_HEIGHT}), "Space Invaders"),
    gameView(sf::FloatRect(sf::Vector2f({0, -constants::SCOREBOARD_HEIGHT}), sf::Vector2f({constants::GAME_WIDTH,constants::GAME_HEIGHT + constants::SCOREBOARD_HEIGHT}))),
    gameLayer(window),
    player_control(gameLayer),
    bullet_control(gameLayer),
    alien_control(gameLayer),
    alien_bullet_control(gameLayer),
    meteor_control(gameLayer),
    ui_control(window)
    {
	
    alien_control.spawnAlien(100, 100, 3);
 
    // limit frame rate
    window.setFramerateLimit(constants::FRAME_RATE);

    // set the view (visible area) for our game
    gameLayer.set_view(gameView);
}

void Game::start() {
    // The clock is needed to control the speed of movement
    sf::Clock clock;

    while (window.isOpen()) {
        // Restart the clock and save the elapsed time into elapsed_time
        sf::Time elapsed_time = clock.restart();
 
        // handle input, check if window is still open
        if (!input()) {
            // update the scene according to the passed time
            update(elapsed_time.asSeconds());
            // draw the scene
            draw();
        }
    }
}

// returns true, if the window has been closed
bool Game::input() {
    while (std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            // quit
            window.close();
            return true;
        }
        
        // Handles key press and release events
        if(const auto* kp = event->getIf<sf::Event::KeyPressed>())
			player_control.keyStateChanged(true, kp->code);
        if(const auto* kp = event->getIf<sf::Event::KeyReleased>())
			player_control.keyStateChanged(false, kp->code);
    }
    return false;
}

void Game::update(float time_passed) {
	player_control.update(time_passed);
	bullet_control.update(time_passed);
    alien_control.update(time_passed);
    meteor_control.update(time_passed);
    alien_bullet_control.update();
}

void Game::draw() {
	// Cleans the screen
    window.clear();
    gameLayer.clear();
    
    // Adds game objects to draw
    player_control.draw();
    bullet_control.draw();
    alien_control.draw();
    alien_bullet_control.draw();
    meteor_control.draw();
    
    ui_control.draw();
    
    // Performs draw calls
    gameLayer.draw();
    
    window.display();
}

// #region Getters/Setters

BulletControl& Game::getBulletControl(){ return bullet_control; };
PlayerControl& Game::getPlayerControl(){ return player_control; };
UIControl& Game::getUIControl(){ return ui_control; };
AlienBulletControl& Game::getAlienBulletControl() {return alien_bullet_control; };

// #endregion
