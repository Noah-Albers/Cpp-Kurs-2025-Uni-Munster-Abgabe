/*
 * AlienControl.h
 *
 *  Created on: 26.07.2025
 *      Author: Olly
 */

#ifndef SRC_CONTROL_ALIENCONTROL_H_
#define SRC_CONTROL_ALIENCONTROL_H_

#include <SFML/Graphics.hpp>
#include "../view/Layer.hpp"
#include "../model/Alien.h"
#include "BulletControl.h"
#include <list>

class AlienControl {
public:
	AlienControl(Layer &layer);
	virtual ~AlienControl();
	
	// Event: When the alien is drawn
	void draw();
	
	// Event: When the game objects shall update
	void update();

	void setBulletList(std::list<Bullet> bullets);

	void spawnAlien(const int x, const int y);
	
protected:
	// Layer to render the player onto
	Layer &layer;
	
	// All Alien objects
	std::list<Alien> aliens;

	// Bullets shot by the player
	std::list<Bullet> bullets;

private:
	//Check if 2 Recktangles overlap
	bool rectsIntersect(const sf::FloatRect& a, const sf::FloatRect& b);
};

#endif /* SRC_CONTROL_ALIENCONTROL_H_ */
