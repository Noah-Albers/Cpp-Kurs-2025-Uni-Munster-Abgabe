/*
 * PropAnimatedSpriteTest.cpp
 *
 *  Created on: 02.08.2025
 *      Author: Noah
 */
 
#include "../../../src/model/properties/PropAnimatedSprite.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <gtest/gtest.h>

TEST(PropSpriteAnimated, check_loop) {
	PropAnimatedSprite sprite("assets/test/Test_2x1.png", 1, 1, 1, 2, true, true);
	
	ASSERT_FALSE(sprite.hasStopped());
	ASSERT_EQ(sprite.getFrame(), 0);
	sprite.updateSprite(1);
	ASSERT_FALSE(sprite.hasStopped());
	ASSERT_EQ(sprite.getFrame(), 1);
	sprite.updateSprite(0.5);
	sprite.updateSprite(0.5);
	ASSERT_FALSE(sprite.hasStopped());
	ASSERT_EQ(sprite.getFrame(), 0);
}

TEST(PropSpriteAnimated, check_none_loop) {
	PropAnimatedSprite sprite("assets/test/Test_2x1.png", 1, 1, 1, 2, false, true);
	
	ASSERT_FALSE(sprite.hasStopped());
	ASSERT_EQ(sprite.getFrame(), 0);
	sprite.updateSprite(1);
	ASSERT_FALSE(sprite.hasStopped());
	ASSERT_EQ(sprite.getFrame(), 1);
	sprite.updateSprite(0.5);
	sprite.updateSprite(0.5);
	ASSERT_TRUE(sprite.hasStopped());
}


