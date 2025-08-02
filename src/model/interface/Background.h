/*
 * Background.h
 *
 *  Created on: 28.07.2025
 *      Author: Noah
 */

#ifndef SRC_MODEL_BACKGROUND_H_
#define SRC_MODEL_BACKGROUND_H_

#include "../properties/PropSprite.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "../../view/Layer.hpp"

class Background : public PropSprite {
public:
	Background();
	
	// Draws the background
	void draw(Layer& layer);
	
	// Updates the object
	void update(const float timePassed);
	
	// Starts a transition to the next background
	void transitionToNextBackground();
	
protected:
	// Percentage to use for smoothly chaning the background
	// If < 0 then there is currently no transition
	// Otherwise between 0.00 to 1.00 when a transition is currently being done
	// Transitions start at 0.00 and go to 1.00
	float transitionPercentage;
	
	// Checks if the background is currently transitioning to a new frame 
	const bool isTransitioning() const;
	
	/**
	 * Updates the transition of the background to the next frame
	 * @pre isTransitioning()
	 */
	void updateTransition(const float timePassed);
};

#endif /* SRC_MODEL_BACKGROUND_H_ */
