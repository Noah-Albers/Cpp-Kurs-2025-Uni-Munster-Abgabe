/*
 * Particle.cpp
 *
 *  Created on: 28.07.2025
 *      Author: Noah
 */

#include "Particle.h"

Particle::Particle(
	const std::filesystem::path& filename,
	const int sizeX, const int sizeY,
	const float scale,
	const int posX, const int posY,
	const float lifeTime
) : PropAnimatedSprite(filename, sizeX, sizeY, scale, lifeTime, false, true)
	{
	sprite.setPosition({(float)posX,(float)posY});
}