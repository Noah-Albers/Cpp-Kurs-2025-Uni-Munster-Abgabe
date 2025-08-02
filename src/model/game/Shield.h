/*
 * Shield.h
 *
 *  Created on: 30.07.2025
 *      Author: Noah
 */

#ifndef SRC_MODEL_ALIENSHIELD_H_
#define SRC_MODEL_ALIENSHIELD_H_

#include "../properties/PropAnimatedSprite.h"
#include <SFML/System/Vector2.hpp>
class Shield : public PropAnimatedSprite {
public:
	Shield(
		const std::filesystem::path& filename,
		const int sizeX, const int sizeY,
		const float scale,
		const float runtime
	);
	
	void setPosition(const sf::Vector2f pos);
};

#endif /* SRC_MODEL_ALIENSHIELD_H_ */
