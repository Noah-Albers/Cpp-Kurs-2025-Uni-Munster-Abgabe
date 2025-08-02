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

// Ensures loop animations work properly
TEST(PropSpriteAnimated, check_loop) {
	// Loads sprite with 2 frames
	PropAnimatedSprite sprite("assets/test/Test_2x1.png", 1, 1, 1, 2, true, true);
	
	// Ensures that the animation is running at beginning and the frame ist 0 (first)
	ASSERT_FALSE(sprite.hasStopped());
	ASSERT_EQ(sprite.getFrame(), 0);
	
	// Lets the animation run for one second (should change frame after that)
	sprite.updateSprite(1);
	
	// Ensure the frame got changed and the animation is still running (bc. its looped)
	ASSERT_FALSE(sprite.hasStopped());
	ASSERT_EQ(sprite.getFrame(), 1);
	
	// Simulates another second pass (but split into two calls)
	sprite.updateSprite(0.5);
	
	// Ensures the frame hasn't changed
	ASSERT_FALSE(sprite.hasStopped());
	ASSERT_EQ(sprite.getFrame(), 1);
	
	// Second part of the split phase
	sprite.updateSprite(0.5);
	
	// Ensures the animation restarts again with frame 0
	ASSERT_FALSE(sprite.hasStopped());
	ASSERT_EQ(sprite.getFrame(), 0);
}


// Ensures none-loop animations work
TEST(PropSpriteAnimated, check_none_loop) {
	// Loads sprite with 2 frames
	PropAnimatedSprite sprite("assets/test/Test_2x1.png", 1, 1, 1, 2, false, true);
	
	// Ensures it isn't stopped at the start and starts with frame 0
	ASSERT_FALSE(sprite.hasStopped());
	ASSERT_EQ(sprite.getFrame(), 0);
	
	// Simulates a 1 second animation
	sprite.updateSprite(1);
	
	// Ensures its still running and has advanced to the next frame
	ASSERT_FALSE(sprite.hasStopped());
	ASSERT_EQ(sprite.getFrame(), 1);
	
	// Simulates another 1 second animation but split into two calls
	sprite.updateSprite(0.5);
	ASSERT_FALSE(sprite.hasStopped());
	ASSERT_EQ(sprite.getFrame(), 1);
	sprite.updateSprite(0.5);
	
	// Ensures the animation stops at the end
	ASSERT_TRUE(sprite.hasStopped());
}


