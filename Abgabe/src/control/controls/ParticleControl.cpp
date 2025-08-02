/*
 * ParticleControl.cpp
 *
 *  Created on: 28.07.2025
 *      Author: Noah
 */

#include "ParticleControl.h"
#include "../properties/PropDrawable.h"

#include "../../assets/AssetMappings.h"
#include "../../model/Constants.hpp"

ParticleControl::ParticleControl(Layer& layer) :
	PropDrawable(layer) {}
	
ParticleControl::~ParticleControl() {}

void ParticleControl::draw(){
	for(auto it = particles.begin(); it != particles.end(); it++)
		layer.add_to_layer(it->getSprite());
}

void ParticleControl::update(const float timePassed){
	// Updates the particles and removes any that have died
	for(auto it = particles.begin(); it != particles.end();){
		it->updateSprite(timePassed);
		
		if(it->hasStopped())
			it = particles.erase(it);
		else
			++it;
	}
}

void ParticleControl::spawnDebugParticle(
		const std::filesystem::path& filename,
		const int sizeX, const int sizeY,
		const float scale,
		const int posX, const int posY,
		const float lifeTime
	) {
	particles.emplace_back(filename, sizeX, sizeY, scale, posX, posY, lifeTime);
}

void ParticleControl::spawnExplosionParticle(const int x, const int y){
	particles.emplace_back(ASSETS_EXPLOSION, x, y, constants::PARTICLE_EXPLOSION_LENGTH);
}

void ParticleControl::spawnPlayerDeathParticle(const int x, const int y) {
	particles.emplace_back(ASSETS_SPRITE_PLAYER_DEATH, x, y, constants::PARTICLE_PLAYER_DEATH_LENGTH);
}

void ParticleControl::spawnMeteorExplosionParticle(const int x, const int y) {
	particles.emplace_back(ASSETS_SPRITE_METEOR_EXPLOSION, x, y, constants::PARTICLE_METEOR_EXPLOSION_LENGTH);
}

const std::list<Particle>& ParticleControl::getParticles() const {return particles;}
