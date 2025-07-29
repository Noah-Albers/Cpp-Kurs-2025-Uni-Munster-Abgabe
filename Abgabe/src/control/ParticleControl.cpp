/*
 * ParticleControl.cpp
 *
 *  Created on: 28.07.2025
 *      Author: Noah
 */

#include "ParticleControl.h"
#include "properties/PropDrawable.h"

#include "../assets/AssetMappings.h"

ParticleControl::ParticleControl(Layer& layer) : PropDrawable(layer) {}

void ParticleControl::draw(){
	for(auto it = particles.begin(); it != particles.end(); it++)
		layer.add_to_layer(it->getSprite());
}

void ParticleControl::update(float time_passed){
	// Updates the particles and removes any that have died
	for(auto it = particles.begin(); it != particles.end();){
		it->updateSprite(time_passed);
		
		if(it->hasStopped())
			it = particles.erase(it);
		else
			++it;
	}
}

void ParticleControl::spawnDebugParticle(
		const std::filesystem::path& filename,
		const int size_x, const int size_y,
		const float scale,
		const int posX, const int posY,
		const float lifeTime
	) {
	particles.emplace_back(filename, size_x, size_y, scale, posX, posY, lifeTime);
}

void ParticleControl::spawnExplosionParticle(const int x, const int y){
	particles.emplace_back(ASSETS_EXPLOSION, x, y, 2);
}

void ParticleControl::spawnPlayerDeathParticle(const int x, const int y) {
	particles.emplace_back(ASSETS_SPRITE_PLAYER_DEATH, x, y, 2);
}

void ParticleControl::spawnMeteorExplosionParticle(const int x, const int y) {
	particles.emplace_back(ASSETS_SPRITE_METEOR_EXPLOSION, x, y, 0.5);
}
