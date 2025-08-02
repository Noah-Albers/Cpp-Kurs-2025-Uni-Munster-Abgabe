#include "Game.hpp"

#include <SFML/Window/Keyboard.hpp>

#include "../model/Constants.hpp"
#include "controls/MeteorControl.h"
#include "controls/ParticleControl.h"
#include "controls/UIControl.h"
#include "controls/BulletControl.h"
#include "controls/PlayerControl.h"
#include "controls/AlienControl.h"

Game::Game() :
	window(sf::VideoMode({constants::GAME_WIDTH, constants::GAME_HEIGHT + constants::SCOREBOARD_HEIGHT}), "Space Invaders"),
    gameView(sf::FloatRect(sf::Vector2f({0, -constants::SCOREBOARD_HEIGHT}), sf::Vector2f({constants::GAME_WIDTH,constants::GAME_HEIGHT + constants::SCOREBOARD_HEIGHT}))),
    uiView(sf::FloatRect(sf::Vector2f({0, 0}), sf::Vector2f({constants::GAME_WIDTH,constants::GAME_HEIGHT + constants::SCOREBOARD_HEIGHT}))),
    gameLayer(window),
    uiLayer(window),
    backgroundLayer(window),
    playerControl(nullptr),
    bulletControl(nullptr),
    alienControl(nullptr),
    alienBulletControl(nullptr),
    meteorControl(nullptr),
    particleControl(nullptr),
    uiControl(nullptr),
    levelControl(nullptr)
    {
    // limit frame rate
    window.setFramerateLimit(constants::FRAME_RATE);

    // set the view (visible area) for our game
    gameLayer.set_view(gameView);
    uiLayer.set_view(uiView);
    backgroundLayer.set_view(uiView);
    
    resetGame();
}

void Game::resetGame() {
	
	// Defines a macro to delete any old controllers that might exist and create the new ones
	#define RESET_CONTROL(controllerPtr, ControllerClass, ...) \
	    if (controllerPtr != nullptr) \
	        delete controllerPtr; \
	    controllerPtr = new ControllerClass(__VA_ARGS__);
	
	// Resets the controllers
	RESET_CONTROL(playerControl, PlayerControl, gameLayer);
	RESET_CONTROL(bulletControl, BulletControl, gameLayer);
	RESET_CONTROL(alienControl, AlienControl, gameLayer);
	RESET_CONTROL(alienBulletControl, AlienBulletControl, gameLayer);
	RESET_CONTROL(meteorControl, MeteorControl, gameLayer);
	RESET_CONTROL(particleControl, ParticleControl, gameLayer);
	RESET_CONTROL(uiControl, UIControl, uiLayer, backgroundLayer);
	RESET_CONTROL(levelControl, LevelControl);
	
	#undef RESET_CONTROL
	
	// Populates all control's
	alienBulletControl->populate(playerControl);
	alienControl->populate(alienBulletControl, levelControl, playerControl);
	bulletControl->populate(alienControl, meteorControl);
	meteorControl->populate(playerControl,particleControl);
	playerControl->populate(bulletControl, particleControl);
	uiControl->populate(playerControl);
    levelControl->populate(alienControl, uiControl);	
}

void Game::start() {
    // The clock is needed to control the speed of movement
    sf::Clock clock;

    while (window.isOpen()) {
        // Restart the clock and save the elapsed time into elapsedTime
        sf::Time elapsedTime = clock.restart();
 
        // handle input, check if window is still open
        if (!input()) {
            // update the scene according to the passed time
            update(elapsedTime.asSeconds());
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
        
        // If the game is over, waits for the restart-key to be pressed
        if(isGameOver()){
			const auto* kp = event->getIf<sf::Event::KeyPressed>();
			if(kp && kp->code == sf::Keyboard::Key::R)
				resetGame();
		
			continue;	
		}
        
        // Handles key press and release events
        if(const auto* kp = event->getIf<sf::Event::KeyPressed>())
			playerControl->keyStateChanged(true, kp->code);			
        if(const auto* kp = event->getIf<sf::Event::KeyReleased>())
			playerControl->keyStateChanged(false, kp->code);
    }
    return false;
}

void Game::update(const float timePassed) {
    levelControl->update();
	playerControl->update(timePassed);
	bulletControl->update(timePassed);
    alienControl->update(timePassed);
    meteorControl->update(timePassed);
    particleControl->update(timePassed);
    alienBulletControl->update(timePassed);
    uiControl->update(timePassed);
}

void Game::draw() {
	// Cleans the screen
    window.clear();
    uiLayer.clear();
    gameLayer.clear();
    
    // Adds game objects to draw
    playerControl->draw();
    bulletControl->draw();
    alienControl->draw();
    alienBulletControl->draw();
    meteorControl->draw();
    particleControl->draw();
    
    uiControl->draw();
    
    // Performs draw calls
    backgroundLayer.draw();
    gameLayer.draw();
    uiLayer.draw();
    
    window.display();
}

const bool Game::isGameOver() const { return playerControl->getPlayer().isDead(); };
