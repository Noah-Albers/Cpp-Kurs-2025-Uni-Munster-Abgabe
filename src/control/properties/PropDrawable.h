/*
 * PropDrawable.h
 *
 *  Created on: 27.07.2025
 *      Author: Noah
 */

#ifndef SRC_CONTROL_PROPERTIES_PROPDRAWABLE_H_
#define SRC_CONTROL_PROPERTIES_PROPDRAWABLE_H_

#include "../../view/Layer.hpp"

class PropDrawable {
public:
	PropDrawable(Layer &layer);
	
	/**
	 * Event: When the object shall be drawn, this method draws any objects to its layer.
	 *
	 * "Abstract" method to be overwritten
	 */
	virtual void draw() = 0;
	
protected:
	// Layer to render the bullets onto
	Layer &layer;
};

#endif /* SRC_CONTROL_PROPERTIES_PROPDRAWABLE_H_ */
