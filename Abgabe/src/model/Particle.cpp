/*
 * Particle.cpp
 *
 *  Created on: 28.07.2025
 *      Author: Noah
 */

#include "Particle.h"

Particle::Particle(
	const std::filesystem::path& filename,
	const int size_x, const int size_y,
	const float scale,
	const int posX, const int posY,
	const float lifeTime
) : PropAnimatedSprite(filename, size_x, size_y, scale, lifeTime, false, true)
	{
	sprite.setPosition({(float)posX,(float)posY});
}