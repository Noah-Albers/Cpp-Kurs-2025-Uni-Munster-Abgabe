// define some constants to make code more readable
#include <cmath>
namespace constants {
	
	// TODO: Maybe make alien shoot chance constant and increment with levels
	
	///////////////////////
	/// Window settings ///
	///////////////////////
	
	// Size of the play-field
    constexpr int GAME_WIDTH = 600; // px
    constexpr int GAME_HEIGHT = 600; // px
    
	// Scoreboard and upper UI height
    constexpr int SCOREBOARD_HEIGHT = 150; // px
    
    // Max amount of frames per second
    constexpr unsigned int FRAME_RATE = 60; // fps
	
	///////////////////////
	// Position Settings //
	///////////////////////
	// Alien Grid spacing settings
    constexpr int ALIEN_SPACE_X = 32; // px
    constexpr int ALIEN_SPACE_Y = 32; // px
    
    // How fast the aliens move per Frame when they spawn and
    // move into the game field
    constexpr float ALIEN_SPAWN_SPEED = 3; // px
    
    ////////////////////
    // Score settings //
    ////////////////////
    // How much each alien kill brings for the total score of the player
    constexpr float SCORE_MULTIPLIER_INCREASE_PER_LEVEL = 1.5; // times
    
	//////////////////////
	// Balance Settings //
	//////////////////////
	
	//
	// Player settings
	//
	// How many lifes the player has
	constexpr int PLAYER_START_LIFES = 5; // lifes
	
	// How fast the player moves per Frame when the keys are pressed
	constexpr float PLAYER_SPEED = 3.5; // px
	
	// How long the player is invulnerable after being hit
	constexpr float INVULNERABILITY_TIME = 2; // sec
	
	// How fast the player bullets travel per frame
	constexpr float PLAYER_BULLET_SPEED = 6; // px
	
	//
	// Alien settings
	//
	// Speed development per level
	constexpr float ALIEN_START_SPEED = 2; // px
	constexpr float ALIEN_SPEED_INCREASE_PER_LEVEL = .2; // px
	constexpr float MAX_ALIEN_SPEED = INFINITY; // px
	
	// Population development per level
	constexpr int ALIEN_START_LIENS_PER_LINE = 1; // aliens
	constexpr int ALIEN_LINE_INCREASE_PER_LEVEL = 2; // aliens
	constexpr int MAX_ALIENS_PER_LINE = 9; // aliens

	constexpr int ALIEN_START_LINE_COUNT = 1; // lines
	constexpr int ALIEN_LINE_AMOUNT_INCREASE_PER_LEVEL = 1; // lines
	constexpr int MAX_ALIEN_LINE_COUNT = 5; // lines
		
	// How fast the alien-bullets fly
	constexpr float ALIEN_BULLET_SPEED = 2.5; // px	
	
	// How far down the aliens move when they get to the end of a line
	constexpr int ALIEN_ADVANCE_SPEED = 30; // px
	
	//
	// Alien Bullet settings
	//
	// How likely it is for an alien to shot per frame
	constexpr float ALIEN_SHOOT_CHANCE = 0.005; // %
	constexpr int MAX_ALIEN_BULLETS = 15; // bullets
	
	//
	// Meteor settings
	//
	// How many seconds are between meteor falls
	constexpr float METEOR_DELAY = 3; // sec
	
	// How fast the meteor moves per Frame
	constexpr float METEOR_SPEED = 2; // px
	
	////////////////////////
	// Animation Settings //
	////////////////////////
	
	// How many pixel the background shall scroll per Frame
	constexpr float BACKGROUND_SCROLL_SPEED = 1.2; // px
	
	// Frequency of the background transition. Eg. 1 <=> 1 second, 0.5 <=> 2 seconds
	constexpr float BACKGROUND_TRANSITION_SPEED = .2; // Hz
	
	//
	// How long each animation plays
	//
	constexpr float ANIMATION_ALIEN_BULLET_LENGTH = .4; // sec
	constexpr float ANIMATION_ALIEN_SHIELD_LENGTH = 1; // sec
	constexpr float ANIMATION_PLAYER_BULLET_LENGTH = 0.6; // sec
	
	constexpr float PARTICLE_PLAYER_DEATH_LENGTH = 2; // sec
	constexpr float PARTICLE_METEOR_EXPLOSION_LENGTH = 0.5; // sec
	constexpr float PARTICLE_EXPLOSION_LENGTH = 2; // sec

	// Player blink speed modifier. Higher value means longer blink frames
	constexpr int PLAYER_BLINK_LENGTH = 30; // modifier
    
}