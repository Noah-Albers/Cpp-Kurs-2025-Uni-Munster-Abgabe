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
	const bool pubIsTransitioning() const { return isTransitioning(); };
	void pubUpdateTransition(const float time_passed) { updateTransition(time_passed); };
};

TEST(BackgroundTest, normal_scrolling) {
	MockBackground bg;
	ASSERT_FALSE(bg.pubIsTransitioning());

	auto frame = bg.getFrame();

	for(int i=0;i<10;i++){
		auto yStart = bg.getSprite().getTextureRect().position.y;
		bg.update(1);	
		auto yStop = bg.getSprite().getTextureRect().position.y;
		
		ASSERT_EQ(frame, bg.getFrame());
		ASSERT_GE(abs(yStart - yStop), 0.1);
	}
}

TEST(BackgroundTest, transition_update) {
	MockBackground bg;
	ASSERT_FALSE(bg.pubIsTransitioning());
	
	auto frame = bg.getFrame();
	
	bg.transitionToNextBackground();
	
	ASSERT_NEAR(bg.getPerc(), 0, 0.001);
	ASSERT_TRUE(bg.pubIsTransitioning());
	
	float before = 0;
	while(bg.pubIsTransitioning()){
		before = bg.getPerc();
		ASSERT_EQ(bg.getFrame(), frame);
		bg.update(0.01);		
	}
	ASSERT_NEAR(before, 1, 0.01);
	
	ASSERT_EQ(bg.getFrame(), (frame+1) % bg.getFrameAmount());
}
