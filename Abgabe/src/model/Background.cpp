/*
 * Background.cpp
 *
 *  Created on: 28.07.2025
 *      Author: Noah
 */

#include "Background.h"
#include "properties/PropSprite.h"

#include "../assets/AssetMappings.h"

Background::Background(int windowSizeX) :
	PropSprite(ASSETS_SPRITE_BACKGROUND)
	{
	float scale = (float)windowSizeX / (float)sprite.getTextureRect().size.x;
	sprite.setScale({scale, scale});
}

