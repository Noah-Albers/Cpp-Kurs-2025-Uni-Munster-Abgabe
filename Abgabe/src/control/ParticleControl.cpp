/*
 * ParticleControl.cpp
 *
 *  Created on: 28.07.2025
 *      Author: Noah
 */

#include "ParticleControl.h"
#include "Game.hpp"
#include "properties/PropDrawable.h"

ParticleControl::ParticleControl(Layer& layer) : PropDrawable(layer) {}

void ParticleControl::draw(){
	for(auto it = particles.begin(); it != particles.end(); it++)
		layer.add_to_layer(it->getSprite());
}

void ParticleControl::update(float time_passed){
	// Updates the particles and removes any that have died
	for(auto it = particles.begin(); it != particles.end();){
		it->update(time_passed);
		
		if(it->isDead())
			it = particles.erase(it);
		else
			++it;
	}
}

