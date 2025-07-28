/*
 * Particle.cpp
 *
 *  Created on: 28.07.2025
 *      Author: Noah
 */

#include "Particle.h"
#include "properties/PropSprite.h"

Particle::Particle(
	const std::filesystem::path& filename,
	const int size_x, const int size_y,
	const int posX, const int posY,
	const float scale,
	const float lifeTime
) : PropSprite(filename, size_x, size_y, 1, true),
	lifeTime(0),
	maxLifeTime(lifeTime)
	{
	sprite.setPosition({(float)posX,(float)posY});
	sprite.setScale({scale, scale});
}

void Particle::update(float time_passed) {
	int frameAmt = getFrameAmount();
	
	// Calculates previous and new frame
	int oldFrame = (int)(lifeTime / maxLifeTime * frameAmt);
	lifeTime+=time_passed;
	int newFrame = (int)(lifeTime / maxLifeTime * frameAmt);
	
	// Only updates the sprite, if the frames are different
	if(oldFrame == newFrame) return;
	setFrame(getFrame()+1);
}

bool Particle::isDead(){
	return lifeTime >= maxLifeTime;
}
