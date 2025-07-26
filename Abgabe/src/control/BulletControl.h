/*
 * BulletController.h
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#ifndef SRC_CONTROL_BULLETCONTROL_H_
#define SRC_CONTROL_BULLETCONTROL_H_

#include <SFML/Graphics.hpp>
#include <list>
#include "../view/Layer.hpp"
#include "../model/Bullet.h"

class BulletControl {
public:
	int smth = 0;

	BulletControl(Layer &layer);
	virtual ~BulletControl();
	
	// Event: When the game objects shall update
	void update();
	
	// Event: When the objects are drawn to the screen
	void draw();
	
	// Spawns a new bullet at the given position
	void spawnBulletAt(const int x, const int y);
	
	
protected:
	// Layer to render the bullets onto
	Layer &layer;

	// List of shot bullets
	std::list<Bullet> bullets;
};

#endif /* SRC_CONTROL_BULLETCONTROL_H_ */
