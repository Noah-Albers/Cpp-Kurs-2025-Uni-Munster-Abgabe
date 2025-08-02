/*
 * MockClasses.cpp
 *
 *  Created on: 31.07.2025
 *      Author: Noah
 *
 * This files holds some common mock classes used by the tests
 *
 */
#include "../src/view/Layer.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

class MockLayer : public Layer {
public:
	MockLayer(sf::RenderWindow& win) : Layer(win) {}
	
	MOCK_METHOD(void, add_to_layer, (const sf::Drawable &drawable), (override));
};
