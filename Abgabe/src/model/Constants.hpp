// define some constants to make code more readable
namespace constants {
    constexpr int GAME_WIDTH = 600;
    constexpr int GAME_HEIGHT = 600;
    constexpr int SCOREBOARD_HEIGHT = 150;
    constexpr unsigned int FRAME_RATE = 60;
	
	constexpr int START_LIFES = 5;
    constexpr float ALIEN_SHOOT_CHANCE = 0.005; // Chance in percent per alien per frame
    constexpr float ALIEN_BULLET_SPEED = 2.5;

    constexpr float ANIMATION_TIME = 0.4; // Time in sec.ms that defines how long an animated sprite runs

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
    constexpr int ALIEN_Y_ADVANCE = 10;
    
    constexpr float BACKGROUND_SCROLL_SPEED = 1.2; // Constant to change the background scroll speed
    constexpr float BACKGROUND_TRANSITION_MODIFIER = .2; // Constant modifier to slow or speed up background transitions
}