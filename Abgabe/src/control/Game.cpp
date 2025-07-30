#include "Game.hpp"

#include <SFML/Window/Keyboard.hpp>

#include "../model/Constants.hpp"
#include "MeteorControl.h"
#include "ParticleControl.h"
#include "UIControl.h"
#include "BulletControl.h"
#include "PlayerControl.h"
#include "AlienControl.h"

// Initialize the singleton
Game::Game() :
	window(sf::VideoMode({constants::GAME_WIDTH, constants::GAME_HEIGHT + constants::SCOREBOARD_HEIGHT}), "Space Invaders"),
    gameView(sf::FloatRect(sf::Vector2f({0, -constants::SCOREBOARD_HEIGHT}), sf::Vector2f({constants::GAME_WIDTH,constants::GAME_HEIGHT + constants::SCOREBOARD_HEIGHT}))),
    uiView(sf::FloatRect(sf::Vector2f({0, 0}), sf::Vector2f({constants::GAME_WIDTH,constants::GAME_HEIGHT + constants::SCOREBOARD_HEIGHT}))),
    gameLayer(window),
    uiLayer(window),
    backgroundLayer(window),
    player_control(nullptr),
    bullet_control(nullptr),
    alien_control(nullptr),
    alien_bullet_control(nullptr),
    meteor_control(nullptr),
    particle_control(nullptr),
    ui_control(nullptr),
    level_control(nullptr)
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
	#define RESET_CONTROL(controller_ptr, ControllerClass, ...) \
	    if (controller_ptr != nullptr) \
	        delete controller_ptr; \
	    controller_ptr = new ControllerClass(__VA_ARGS__);
	
	// Resets the controllers
	RESET_CONTROL(player_control, PlayerControl, gameLayer);
	RESET_CONTROL(bullet_control, BulletControl, gameLayer);
	RESET_CONTROL(alien_control, AlienControl, gameLayer);
	RESET_CONTROL(alien_bullet_control, AlienBulletControl, gameLayer);
	RESET_CONTROL(meteor_control, MeteorControl, gameLayer);
	RESET_CONTROL(particle_control, ParticleControl, gameLayer);
	RESET_CONTROL(ui_control, UIControl, uiLayer, backgroundLayer);
	RESET_CONTROL(level_control, LevelControl);
	
	#undef RESET_CONTROL
	
	// Populates all control's
	alien_bullet_control->populate(player_control);
	alien_control->populate(alien_bullet_control, level_control, player_control);
	bullet_control->populate(alien_control, meteor_control);
	meteor_control->populate(player_control,particle_control);
	player_control->populate(bullet_control, particle_control);
	ui_control->populate(player_control);
    level_control->populate(alien_control, ui_control);	
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
        
        // If the game is over, waits for the restart-key to be pressed
        if(isGameOver()){
			const auto* kp = event->getIf<sf::Event::KeyPressed>();
			if(kp && kp->code == sf::Keyboard::Key::R)
				resetGame();
		
			continue;	
		}
        
        // Handles key press and release events
        if(const auto* kp = event->getIf<sf::Event::KeyPressed>())
			player_control->keyStateChanged(true, kp->code);			
        if(const auto* kp = event->getIf<sf::Event::KeyReleased>())
			player_control->keyStateChanged(false, kp->code);
    }
    return false;
}

void Game::update(const float time_passed) {
    level_control->update();
	player_control->update(time_passed);
	bullet_control->update(time_passed);
    alien_control->update(time_passed);
    meteor_control->update(time_passed);
    particle_control->update(time_passed);
    alien_bullet_control->update(time_passed);
    ui_control->update(time_passed);
}

void Game::draw() {
	// Cleans the screen
    window.clear();
    uiLayer.clear();
    gameLayer.clear();
    
    // Adds game objects to draw
    player_control->draw();
    bullet_control->draw();
    alien_control->draw();
    alien_bullet_control->draw();
    meteor_control->draw();
    particle_control->draw();
    
    ui_control->draw();
    
    // Performs draw calls
    backgroundLayer.draw();
    gameLayer.draw();
    uiLayer.draw();
    
    window.display();
}

const bool Game::isGameOver() const { return player_control->getPlayer().isDead(); };
