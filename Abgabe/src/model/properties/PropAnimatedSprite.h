/*
 * PropAnimatedSprite.h
 *
 *  Created on: 28.07.2025
 *      Author: Noah
 */

#ifndef SRC_MODEL_PROPERTIES_PROPANIMATEDSPRITE_H_
#define SRC_MODEL_PROPERTIES_PROPANIMATEDSPRITE_H_

#include "PropSprite.h"

class PropAnimatedSprite : public PropSprite {
public:
	PropAnimatedSprite(const std::filesystem::path& filename, const int sizeX, const int sizeY, const float scale, const float runTimeInSec, const bool loop, const bool centerOrigin = false);
	
	// When the frame shall update
	void updateSprite(float timePassed);
	
	// Returns if the animation is over. Note: Looping animations wont stop duh
	bool hasStopped() const;
protected:
	// If the sprite shall loop after its done
	bool loop;
	
	// How long it shall run in general and the 
	float fullRunTime, runtime;
};

#endif /* SRC_MODEL_PROPERTIES_PROPANIMATEDSPRITE_H_ */
