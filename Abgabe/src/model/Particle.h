/*
 * Particle.h
 *
 *  Created on: 28.07.2025
 *      Author: Noah
 */

#ifndef SRC_MODEL_PARTICLE_H_
#define SRC_MODEL_PARTICLE_H_

#include "./properties/PropSprite.h"

class Particle : public PropSprite {
public:
	Particle(
		const std::filesystem::path& filename,
		const int size_x, const int size_y,
		const int posX, const int posY,
		const float scale,
		const float lifeTime
	);
	
	// Event: When the particle shall update
	void update(float time_passed);

	// Returns if the particle has died (lifetime has reached zero)
	bool isDead();

protected:
	// How much time the particle has to live and what its max lifetime is
	float lifeTime, maxLifeTime;
};

#endif /* SRC_MODEL_PARTICLE_H_ */
