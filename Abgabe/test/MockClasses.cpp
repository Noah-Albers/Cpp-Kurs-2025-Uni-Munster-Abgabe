/*
 * MockClasses.cpp
 *
 *  Created on: 31.07.2025
 *      Author: Noah
 */

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../src/control/controls/PlayerControl.h"
#include "../src/control/controls/BulletControl.h"
#include "../src/control/controls/ParticleControl.h"
#include "../src/view/Layer.hpp"


class MockLayer : public Layer {
public:
	MockLayer(sf::RenderWindow& win) : Layer(win) {}
	
	MOCK_METHOD(void, add_to_layer, (const sf::Drawable &drawable), (override));
};

class MockPlayerControl : public PlayerControl {
public:
	MockPlayerControl(Layer& layer) : PlayerControl(layer) {}
};

class MockBulletControl : public BulletControl {
public:
	MockBulletControl(Layer& layer) : BulletControl(layer) {}

};

class MockParticleControl : public ParticleControl {
public:
	MockParticleControl(Layer& layer) : ParticleControl(layer) {}
	
};


