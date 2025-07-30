/*
 * UIControl.cpp
 *
 *  Created on: 27.07.2025
 *      Author: Noah
 */

#include "UIControl.h"
#include <SFML/Graphics/Rect.hpp>
#include "../model/Constants.hpp"
#include "PlayerControl.h"
#include "../assets/AssetMappings.h"


UIControl::UIControl(Layer& uiLayer, Layer& backgroundLayer) :
	uiLayer(uiLayer),
	backgroundLayer(backgroundLayer),
	scoreboard(font),
	healthbar(10, 60),
	deathmessage(font)
	{
		
	// Loads the font
	if (!font.openFromFile(ASSETS_FONT_DEFAULT))
        throw std::runtime_error("Failed to load Font");

	scoreboard.initialize(10);
	deathmessage.initialize();
		
	// Sets the initial score
	setScore(0);
}

void UIControl::populate(PlayerControl* playerControl){
	this->playerControl = playerControl;
}

void UIControl::update(const float time_passed){
	background.update(time_passed);
}

void UIControl::nextBackground(){
	background.transitionToNextBackground();
}

void UIControl::setScore(const int newScore){
	score = newScore;
	scoreboard.displayScore(score);
}

void UIControl::draw() {
	background.draw(backgroundLayer);
	scoreboard.draw(uiLayer);
	healthbar.drawBar(uiLayer,
		playerControl->getPlayer().getLifes(),
		constants::START_LIFES
	);
	
	if(playerControl->getPlayer().isDead())
		deathmessage.draw(uiLayer);
};
