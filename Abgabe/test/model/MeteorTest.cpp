
#include <SFML/System/Vector2.hpp>
#include <gtest/gtest.h>
#include "../../src/model/game/Meteor.h"
#include "../../src/model/Constants.hpp"

TEST(MeteorTest, constructor) {
	Meteor meteor(10, 20);
	
	ASSERT_EQ(meteor.getPosition(), sf::Vector2f(10, 20 - meteor.getSprite().getLocalBounds().size.y));
}
