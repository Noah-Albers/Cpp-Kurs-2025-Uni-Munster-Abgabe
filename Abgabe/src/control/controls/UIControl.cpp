/*
 * UIControl.cpp
 *
 *  Created on: 27.07.2025
 *      Author: Noah
 */

#include "UIControl.h"
#include <SFML/Graphics/Rect.hpp>
#include "../../model/Constants.hpp"
#include "PlayerControl.h"
#include "../../assets/AssetMappings.h"

UIControl::UIControl(Layer& uiLayer, Layer& backgroundLayer) :
	uiLayer(uiLayer),
	backgroundLayer(backgroundLayer),
	scoreboard(font),
	healthbar(10, 90),
	shieldbar(10, 55),
	deathmessage(font)
	{
	// Loads the font
	if (!font.openFromFile(ASSETS_FONT_DEFAULT))
        throw std::runtime_error("Failed to load Font");

	scoreboard.initialize(10);
	scoreboard.displayScore(0);
	deathmessage.initialize();

}

UIControl::~UIControl() {};

void UIControl::populate(PlayerControl* playerControl){
	this->playerControl = playerControl;
}

void UIControl::update(const float time_passed){
	background.update(time_passed);
}

void UIControl::nextBackground(){
	background.transitionToNextBackground();
}

void UIControl::displayScore(const int newScore) {
	scoreboard.displayScore(newScore);
}

void UIControl::draw() {
	background.draw(backgroundLayer);
	scoreboard.draw(uiLayer);
	healthbar.drawBar(uiLayer,
		playerControl->getPlayer().getLifes(),
		constants::PLAYER_START_LIFES
	);
	shieldbar.drawBar(uiLayer, playerControl->getPlayer().getShieldbar());
	
	if(playerControl->getPlayer().isDead())
		deathmessage.draw(uiLayer);
};
