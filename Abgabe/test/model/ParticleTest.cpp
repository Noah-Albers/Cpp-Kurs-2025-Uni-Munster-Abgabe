
#include "../../src/model/game/Particle.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <gtest/gtest.h>

TEST(Particle, constructor_1) {
	Particle part("assets/test/Test_1x1.png", 1, 1, 1, 9, 18, 10);
	
	ASSERT_NEAR(part.getSprite().getPosition().x, 9, 0.0001);
	ASSERT_NEAR(part.getSprite().getPosition().y, 18, 0.0001);	
}

TEST(Particle, constructor_2) {
	Particle part("assets/test/Test_1x1.png", 1, 1, 1, 2, 99, 10);
	
	ASSERT_NEAR(part.getSprite().getPosition().x, 2, 0.0001);
	ASSERT_NEAR(part.getSprite().getPosition().y, 99, 0.0001);	
}

TEST(Particle, constructor_3) {
	Particle part("assets/test/Test_1x1.png", 1, 1, 1, -10, -4, 10);
	
	ASSERT_NEAR(part.getSprite().getPosition().x, -10, 0.0001);
	ASSERT_NEAR(part.getSprite().getPosition().y, -4, 0.0001);	
}

