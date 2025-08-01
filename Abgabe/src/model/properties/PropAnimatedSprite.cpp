/*
 * PropAnimatedSprite.cpp
 *
 *  Created on: 28.07.2025
 *      Author: Noah
 */

#include "PropAnimatedSprite.h"
#include "PropSprite.h"

PropAnimatedSprite::PropAnimatedSprite(
	const std::filesystem::path& filename,
	const int sizeX, const int sizeY,
	const float scale,
	const float runTimeInSec, const bool loop,
	const bool centerOrigin
) : PropSprite(filename, sizeX, sizeY, scale, centerOrigin),
	loop(loop),
	fullRunTime(runTimeInSec),
	runtime(0) {}

bool PropAnimatedSprite::hasStopped() const {
	return runtime <= -1;
}

void PropAnimatedSprite::updateSprite(float timePassed){
	// Ensures less calculations for sprites that have reached their end of life
	if(runtime > fullRunTime && !loop) return;
	if(runtime == -1) return;
	
	int frameAmt = getFrameAmount();
	
	// Calculates previous and new frame
	int oldFrame = (int)(runtime / fullRunTime * frameAmt);
	runtime+=timePassed;
	int newFrame = (int)(runtime / fullRunTime * frameAmt);
	
	// Only updates the sprite, if the frames are different
	if(oldFrame == newFrame) return;

	if(newFrame >= frameAmt){
		// Resets the loop
		if(loop){
			setFrame(0);
			runtime = 0;
		}else
			// Marks the prop as over
			runtime = -1;
	}else if(oldFrame < newFrame){
		// Otherwise advances the frame
		setFrame(getFrame()+1);
		
	}
}
