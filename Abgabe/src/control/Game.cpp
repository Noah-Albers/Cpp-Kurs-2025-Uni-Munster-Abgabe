#include "Game.hpp"

#include <SFML/Window/Keyboard.hpp>

#include "../model/Constants.hpp"
#include "BulletControl.h"
#include "PlayerControl.h"
#include "AlienControl.h"

// Initialize the static member to nullptr
Game& Game::instance = *(new Game());

 Game& Game::getInstance() {
    return instance;
}

Game::Game() :
	window(sf::VideoMode({constants::VIEW_WIDTH, constants::VIEW_HEIGHT}), "Space Invaders"),
    view(sf::FloatRect(sf::Vector2f({0, 0}), sf::Vector2f({constants::VIEW_WIDTH,constants::VIEW_HEIGHT}))),
    game_layer(window),
    player_control(game_layer),
    bullet_control(game_layer),
    alien_control(game_layer)
    {
	
    alien_control.spawnAlien(100, 100);
 
    // limit frame rate
    window.setFramerateLimit(constants::FRAME_RATE);

    // set the view (visible area) for our game
    game_layer.set_view(view);
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
	player_control.update();
	bullet_control.update();
    alien_control.update();
}

void Game::draw() {
	// Cleans the screen
    window.clear();
    game_layer.clear();
    
    // Adds game objects to draw
    player_control.draw();
    bullet_control.draw();
    alien_control.draw();
    
    // Performs draw calls
    game_layer.draw();
    window.display();
}

// #region Getters/Setters

BulletControl& Game::getBulletControl(){ return bullet_control; };

// #endregion
