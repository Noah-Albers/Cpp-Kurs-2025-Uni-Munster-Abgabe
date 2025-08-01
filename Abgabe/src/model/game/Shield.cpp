/*
 * Shield.cpp
 *
 *  Created on: 30.07.2025
 *      Author: Noah
 */

#include "Shield.h"

#include <SFML/System/Vector2.hpp>
#include "../Constants.hpp"

Shield::Shield(
	const std::filesystem::path& filename,
	const int size_x, const int size_y,
	const float scale,
	const float runtime
) : PropAnimatedSprite(
		filename, size_x, size_y, scale, runtime,
		true, true
	) {}

void Shield::setPosition(const sf::Vector2f pos){
	sprite.setPosition(pos);
}

