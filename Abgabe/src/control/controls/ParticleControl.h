/*
 * ParticleControl.h
 *
 *  Created on: 28.07.2025
 *      Author: Noah
 */

#ifndef SRC_CONTROL_PARTICLECONTROL_H_
#define SRC_CONTROL_PARTICLECONTROL_H_

#include "../properties/PropDrawable.h"
#include <list>
#include "../../model/game/Particle.h"

class ParticleControl : public PropDrawable {
public:
	ParticleControl(Layer& layer);
	virtual ~ParticleControl();
	
	// Event: When the game objects shall update
	virtual void update(const float time_passed);
	
	// Methods to spawn particles at given positions
	
	virtual void spawnPlayerDeathParticle(const int x, const int y);
	virtual void spawnMeteorExplosionParticle(const int x, const int y);
	virtual void spawnExplosionParticle(const int x, const int y);
	
	// Debug-method to spawn any sprite as a particle at a given position
	void spawnDebugParticle(
		const std::filesystem::path& filename,
		const int size_x, const int size_y,
		const float scale,
		const int posX, const int posY,
		const float lifeTime
	);
	
	virtual void draw() override;

	const std::list<Particle>& getParticles() const;
	
protected:
	// List of particles
	std::list<Particle> particles;
};

#endif /* SRC_CONTROL_PARTICLECONTROL_H_ */
