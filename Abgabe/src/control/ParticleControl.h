/*
 * ParticleControl.h
 *
 *  Created on: 28.07.2025
 *      Author: Noah
 */

#ifndef SRC_CONTROL_PARTICLECONTROL_H_
#define SRC_CONTROL_PARTICLECONTROL_H_

#include "properties/PropDrawable.h"
#include <list>
#include "../model/Particle.h"

class ParticleControl : public PropDrawable {
public:
	ParticleControl(Layer& layer);
	
	// Event: When the game objects shall update
	void update(float time_passed);
	
	// Methods to spawn particles at given positions
	void spawnPlayerDeathParticle(const int x, const int y);
	
	virtual void draw() override;
	
protected:
	// List of particles
	std::list<Particle> particles;
};

#endif /* SRC_CONTROL_PARTICLECONTROL_H_ */
