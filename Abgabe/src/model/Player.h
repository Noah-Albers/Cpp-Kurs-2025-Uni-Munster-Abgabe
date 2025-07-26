/*
 * Player.h
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#ifndef SRC_MODEL_PLAYER_H_
#define SRC_MODEL_PLAYER_H_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../utils/Directions.h"

class Player {
public:
	Player();
	virtual ~Player();
	
	sf::Sprite getSprite();
	void moveBy(int x, int y);
	void setVerticalDirection(VerticalDirection dir);
	void setHorizontalDirection(HorizontalDirection dir);
	
	// Event: When the object shall update
	void update();
	
protected:
    // Texture and sprite for the player
    sf::Texture texture;
    sf::Sprite sprite;
    
	// Vertical and horizonal movement direction's
	HorizontalDirection h_dir;
	VerticalDirection v_dir;
	
	// Multiplier to set the player speed
	float speed;
	
};

#endif /* SRC_MODEL_PLAYER_H_ */
