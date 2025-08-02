/*
 * BackgroundTest.cpp
 *
 *  Created on: 02.08.2025
 *      Author: Noah
 */

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <gtest/gtest.h>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include "../../../src/model/interface/Background.h"
#include "../../CommonMockClasses.cpp"

class MockBackground : public Background {
public:
	float getPerc(){ return transitionPercentage; };
	const bool forwardIsTransitioning() const { return isTransitioning(); };
	void forwardUpdateTransition(const float time_passed) { updateTransition(time_passed); };
};

// Ensures that normally scrolling the background works
TEST(BackgroundTest, normal_scrolling) {
	MockBackground bg;
	ASSERT_FALSE(bg.forwardIsTransitioning());

	auto frame = bg.getFrame();

	// Checks a few times that the texture is actually being scrolled
	for(int i=0;i<10;i++){
		auto yStart = bg.getSprite().getTextureRect().position.y;
		bg.update(1);	
		auto yStop = bg.getSprite().getTextureRect().position.y;
		
		ASSERT_EQ(frame, bg.getFrame());
		ASSERT_GE(abs(yStart - yStop), 0.1);
	}
}

// Ensures that the background transition works
TEST(BackgroundTest, transition_update) {
	MockBackground bg;
	ASSERT_FALSE(bg.forwardIsTransitioning());
	
	auto frame = bg.getFrame();
	
	// Starts a transition
	bg.transitionToNextBackground();
	
	// Ensures that the transition values all are set correctly at the start
	ASSERT_NEAR(bg.getPerc(), 0, 0.001);
	ASSERT_TRUE(bg.forwardIsTransitioning());
	
	// Simulates the full transition
	int tryCtr = 9999;
	float before = 0; // Stores the last percentage value before the transition was over
	while(bg.forwardIsTransitioning() && tryCtr >= 0){
		before = bg.getPerc();
		ASSERT_EQ(bg.getFrame(), frame);
		bg.update(0.01);
		--tryCtr;		
	}
	ASSERT_NE(tryCtr, -1);
	// Ensures the transition goes near 1.00 as the finish
	ASSERT_NEAR(before, 1, 0.01);
	
	// Ensures the frame is actually advanced
	ASSERT_EQ(bg.getFrame(), (frame+1) % bg.getFrameAmount());
}
