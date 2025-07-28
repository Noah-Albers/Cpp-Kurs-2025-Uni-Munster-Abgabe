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
	const int posX, const int posY,
	const float scale,
	const float lifeTime
) : PropAnimatedSprite(filename, size_x, size_y, lifeTime, false, scale, true)
	{
	sprite.setPosition({(float)posX,(float)posY});
	sprite.setScale({scale, scale});
}