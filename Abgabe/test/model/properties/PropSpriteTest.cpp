/*
 * PropSpriteTest.cpp
 *
 *  Created on: 02.08.2025
 *      Author: Noah
 */
 
#include "../../../src/model/properties/PropSprite.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <gtest/gtest.h>

class MockPropSprite : public PropSprite {
	public:
		MockPropSprite(const std::filesystem::path& filename, const int size_x, const int size_y, const float scale, const bool centerOrigin)
		: PropSprite(filename, size_x, size_y, scale, centerOrigin) {}
	
		void setPosition(const int x, const int y) {
			sprite.setPosition(sf::Vector2f(x,y));
		}
};

TEST(PropSprite, constructor_1) {
	PropSprite prop("assets/test/Test.png", 8, 5, 2.5, true);
	
	auto& sprite = prop.getSprite();
	auto& texture = sprite.getTextureRect();
	
	ASSERT_EQ(prop.getFrame(), 0);
	ASSERT_EQ(sprite.getScale().x, 2.5);
	ASSERT_EQ(sprite.getScale().y, 2.5);
	ASSERT_EQ(sprite.getPosition().x, 0);
	ASSERT_EQ(sprite.getPosition().y, 0);
	ASSERT_EQ(sprite.getOrigin().x, 8.0/2.0);
	ASSERT_EQ(sprite.getOrigin().y, 5.0/2.0);
	
	ASSERT_EQ(texture, sf::IntRect({0,0}, {8,5}));
}

TEST(PropSprite, constructor_2) {
	PropSprite prop("assets/test/Test.png", 8, 5, 6.1, false);
	
	auto& sprite = prop.getSprite();
	auto& texture = sprite.getTextureRect();
	
	ASSERT_EQ(prop.getFrame(), 0);
	ASSERT_NEAR(sprite.getScale().x, 6.1, 0.0001);
	ASSERT_NEAR(sprite.getScale().y, 6.1, 0.0001);
	ASSERT_EQ(sprite.getPosition().x, 0);
	ASSERT_EQ(sprite.getPosition().y, 0);
	ASSERT_EQ(sprite.getOrigin().x, 0);
	ASSERT_EQ(sprite.getOrigin().y, 0);
	
	ASSERT_EQ(texture, sf::IntRect({0,0}, {8,5}));
}

TEST(PropSprite, isCollidingWith_1) {
	MockPropSprite a("assets/test/Test.png", 8, 5, 1, false);
	MockPropSprite b("assets/test/Test.png", 8, 5, 1, false);
	
	ASSERT_TRUE(a.isCollidingWith(b, 0));
}

TEST(PropSprite, isCollidingWith_2) {
	MockPropSprite a("assets/test/Test.png", 8, 5, 1, false);
	MockPropSprite b("assets/test/Test.png", 8, 5, 1, false);
	
	a.setPosition(0,5);
	
	ASSERT_FALSE(a.isCollidingWith(b, 0));
}


TEST(PropSprite, isCollidingWith_3) {
	MockPropSprite a("assets/test/Test.png", 8, 5, 1, false);
	MockPropSprite b("assets/test/Test.png", 8, 5, 1, false);
	
	a.setPosition(0,4);
	
	ASSERT_TRUE(a.isCollidingWith(b, 0));
}

TEST(PropSprite, isCollidingWith_4) {
	MockPropSprite a("assets/test/Test.png", 8, 5, 1, false);
	MockPropSprite b("assets/test/Test.png", 8, 5, 1, false);
	
	a.setPosition(0,4);
	
	ASSERT_FALSE(a.isCollidingWith(b, 1));
}

TEST(PropSprite, setFrame_getFrame) {
	PropSprite prop("assets/test/Test.png", 8, 5, 1, false);
	
	ASSERT_EQ(prop.getFrame(), 0);
	prop.setFrame(prop.getFrame()+1);
	ASSERT_EQ(prop.getFrame(), 1);
	prop.setFrame(prop.getFrame()+1);
	ASSERT_EQ(prop.getFrame(), 2);
	prop.setFrame(prop.getFrame()+1);
	ASSERT_EQ(prop.getFrame(), 0);
}


TEST(PropSprite, getFrameAmount_1) {
	PropSprite prop("assets/test/Test.png", 8, 5, 1, false);
	
	ASSERT_EQ(prop.getFrameAmount(), 3);
}

TEST(PropSprite, getFrameAmount_2) {
	PropSprite prop("assets/test/Test_1x1.png", 1, 1, 1, false);
	
	ASSERT_EQ(prop.getFrameAmount(), 1);
}

TEST(PropSprite, getFrameAmount_3) {
	PropSprite prop("assets/test/Test_2x1.png", 1, 1, 1, false);
	
	ASSERT_EQ(prop.getFrameAmount(), 2);
}
