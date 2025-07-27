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
#include "./properties/PropDrawable.h"

class BulletControl : public PropDrawable {
public:
	BulletControl(Layer &layer);
	virtual ~BulletControl();
	
	// Event: When the game objects shall update
	void update();
	
	// Spawns a new bullet at the given position
	void spawnBulletAt(const int x, const int y);
	
	virtual void draw() override;
	
protected:
	// List of shot bullets
	std::list<Bullet> bullets;
};

#endif /* SRC_CONTROL_BULLETCONTROL_H_ */
