
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "../../src/control/controls/PlayerControl.h"
#include "../../src/control/controls/BulletControl.h"
#include "../../src/control/controls/ParticleControl.h"

class MockLayer : public Layer {
public:
	MockLayer(sf::RenderWindow& win) : Layer(win) {}
	
	MOCK_METHOD(void, add_to_layer, (const sf::Drawable &drawable), (override));
	MOCK_METHOD(void, clear, (), (override));
};

class MockPlayerControl : public PlayerControl {
public:
	MockPlayerControl(Layer& layer) : PlayerControl(layer) {}
};

class MockBulletControl : public BulletControl {

};

class MockParticleControl : public ParticleControl {
	
};

TEST(PlayerControl, create) {
	sf::RenderWindow window(sf::VideoMode({10, 10}), "");
	MockLayer layer(window);
	
	//MockBulletControl bulletCtrl(layer);
	//MockParticleControl partCtrl(layer);	
	PlayerControl ctrl(layer);
	
	EXPECT_CALL(layer, add_to_layer(testing::_))
        .Times(1);

	ctrl.draw();

}


