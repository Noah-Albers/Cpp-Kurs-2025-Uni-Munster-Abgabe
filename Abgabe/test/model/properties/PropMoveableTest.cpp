

#include "../../../src/model/properties/PropMoveable.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <gtest/gtest.h>

class MockPropMoveable : public PropMoveable {
public:
	sf::Vector2f pos;

	MockPropMoveable(const float speed, const VerticalDirection v_dir, const HorizontalDirection h_dir) :
		PropMoveable(speed, v_dir, h_dir) {}
			
	virtual void setPosition(const sf::Vector2f position) override { pos = position; };
	virtual const sf::Vector2f getPosition() const override { return pos; };
};

TEST(PropMoveable, constructor_1) {
	MockPropMoveable prop(4.5, VerticalDirection::NONE, HorizontalDirection::NONE);
	
	ASSERT_NEAR(prop.getSpeed(), 4.5, 0.0001);
	ASSERT_EQ(prop.getHorizontalDirection(), HorizontalDirection::NONE);
	ASSERT_EQ(prop.getVerticalDirection(), VerticalDirection::NONE);
}

TEST(PropMoveable, constructor_2) {
	MockPropMoveable prop(-1.3, VerticalDirection::UP, HorizontalDirection::LEFT);
	
	ASSERT_NEAR(prop.getSpeed(), 0, 0.0001);
	ASSERT_EQ(prop.getHorizontalDirection(), HorizontalDirection::LEFT);
	ASSERT_EQ(prop.getVerticalDirection(), VerticalDirection::UP);
}

TEST(PropMoveable, setSpeed) {
	MockPropMoveable prop(0, VerticalDirection::NONE, HorizontalDirection::NONE);
	
	prop.setSpeed(10);
	ASSERT_NEAR(prop.getSpeed(), 10, 0.0001);
	prop.setSpeed(100);
	ASSERT_NEAR(prop.getSpeed(), 100, 0.0001);
	prop.setSpeed(0);
	ASSERT_NEAR(prop.getSpeed(), 0, 0.0001);
	prop.setSpeed(-3);
	ASSERT_NEAR(prop.getSpeed(), 0, 0.0001);
}

TEST(PropMoveable, moveBy) {
	MockPropMoveable prop(10, VerticalDirection::NONE, HorizontalDirection::NONE);
	prop.setPosition(sf::Vector2f(0,0));
	ASSERT_EQ(prop.getPosition(), sf::Vector2f(0,0));
	
	prop.moveBy(10, 15);
	ASSERT_EQ(prop.getPosition(), sf::Vector2f(10,15));
	prop.moveBy(20, -5);
	ASSERT_EQ(prop.getPosition(), sf::Vector2f(10+20,15-5));
	prop.moveBy(-100, 0);
	ASSERT_EQ(prop.getPosition(), sf::Vector2f(10+20-100,15-5+0));
}

TEST(PropMoveable, updatePosition_1) {
	MockPropMoveable prop(10, VerticalDirection::NONE, HorizontalDirection::NONE);
	prop.updatePosition(1);
	
	ASSERT_NEAR(prop.getPosition().x, 0,0.001);
	ASSERT_NEAR(prop.getPosition().y, 0,0.001);
}

TEST(PropMoveable, updatePosition_2) {
	MockPropMoveable prop(100, VerticalDirection::DOWN, HorizontalDirection::NONE);
	prop.updatePosition(1);
	
	ASSERT_NEAR(prop.getPosition().x, 0, 0.001);
	ASSERT_GT(prop.getPosition().y, 1);
}

TEST(PropMoveable, updatePosition_3) {
	MockPropMoveable prop(100, VerticalDirection::UP, HorizontalDirection::NONE);
	prop.updatePosition(1);
	
	ASSERT_NEAR(prop.getPosition().x, 0, 0.001);
	ASSERT_LT(prop.getPosition().y, 1);
}

TEST(PropMoveable, updatePosition_4) {
	MockPropMoveable prop(100, VerticalDirection::NONE, HorizontalDirection::LEFT);
	prop.updatePosition(1);
	
	ASSERT_NEAR(prop.getPosition().y, 0, 0.001);
	ASSERT_LT(prop.getPosition().x, 1);
}
TEST(PropMoveable, updatePosition_5) {
	MockPropMoveable prop(100, VerticalDirection::NONE, HorizontalDirection::RIGHT);
	prop.updatePosition(1);
	
	ASSERT_NEAR(prop.getPosition().y, 0, 0.001);
	ASSERT_GT(prop.getPosition().x, 1);
}




