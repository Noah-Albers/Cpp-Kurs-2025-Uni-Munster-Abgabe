/*
 * Background.cpp
 *
 *  Created on: 28.07.2025
 *      Author: Noah
 */

#include "Background.h"
#include "properties/PropSprite.h"

Background::Background(int windowSizeX) :
	PropSprite("assets/sprites/background.png", 720, 1080)
	{
	float scale = (float)windowSizeX / (float)sprite.getTextureRect().size.x;
	sprite.setScale({scale, scale});
}

