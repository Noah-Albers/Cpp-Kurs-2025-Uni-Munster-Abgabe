// define some constants to make code more readable
namespace constants {
	
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
	
	//////////////////////
	// Balance Settings //
	//////////////////////
	
	// How many lifes the player has
	constexpr int PLAYER_START_LIFES = 5;
	
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




	// TODO

    constexpr float ALIEN_SHOOT_CHANCE = 0.005; // Chance in percent per alien per frame
    constexpr float ALIEN_BULLET_SPEED = 2.5;

    constexpr float ALIEN_BASE_SPEED = 5;
    constexpr float ALIEN_SPEED_INCREASE_PER_LEVEL = 5;
    constexpr int ALIEN_INCREASE_PER_LEVEL = 3;
    constexpr int ALIEN_LINE_INCREASE_PER_LEVEL = 1;
    constexpr float SCORE_MULTIPLIER_PER_LEVEL = 1.5;
    constexpr int MAX_ALIEN_PER_LINE = 10;
    constexpr int MAX_ALIEN_TOTAL = 50;
    constexpr int MAX_ALIENT_BULLETS = 15;

    constexpr int ALIEN_SPACE_X = 32;
    constexpr int ALIEN_SPACE_Y = 32;
    constexpr int ALIEN_Y_ADVANCE = 30;
    
}