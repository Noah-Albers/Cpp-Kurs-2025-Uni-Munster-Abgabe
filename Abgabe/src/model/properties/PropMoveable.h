/*
 * PropMoveable.h
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#ifndef SRC_MODEL_PROPERTIES_PROPMOVEABLE_H_
#define SRC_MODEL_PROPERTIES_PROPMOVEABLE_H_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include "../../utils/Directions.h"

class PropMoveable {
public:
	PropMoveable(
		const float speed = 1,
		const VerticalDirection v_dir = VerticalDirection::NONE,
		const HorizontalDirection h_dir = HorizontalDirection::NONE
	);
	virtual ~PropMoveable();
	
	
	// Event: When the object shall update its position
	void updatePosition();
	
	// Moves the object relative to its current position
	void moveBy(const int x, const int y);
	
	// "abstract" Getter and setter to modify the actual position of the object
	// Required to be overwritten
	virtual void setPosition(const sf::Vector2f position) = 0;
	virtual sf::Vector2f getPosition() = 0;
	
	// Getters/Setters
	void setVerticalDirection(const VerticalDirection dir);
	void setHorizontalDirection(const HorizontalDirection dir);
	void setSpeed(const float speed);
	
protected:
	
	// Vertical and horizonal movement direction's
	HorizontalDirection h_dir;
	VerticalDirection v_dir;
	
	// Multiplier to set the movement speed
	float speed;
};

#endif /* SRC_MODEL_PROPERTIES_PROPMOVEABLE_H_ */
