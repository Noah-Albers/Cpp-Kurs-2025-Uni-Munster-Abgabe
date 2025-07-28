/*
 * Particle.h
 *
 *  Created on: 28.07.2025
 *      Author: Noah
 */

#ifndef SRC_MODEL_PARTICLE_H_
#define SRC_MODEL_PARTICLE_H_

#include "./properties/PropAnimatedSprite.h"

class Particle : public PropAnimatedSprite {
public:
	Particle(
		const std::filesystem::path& filename,
		const int size_x, const int size_y,
		const int posX, const int posY,
		const float scale,
		const float lifeTime
	);
};

#endif /* SRC_MODEL_PARTICLE_H_ */
