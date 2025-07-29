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

UIControl::UIControl(Layer& uiLayer, Layer& backgroundLayer) :
	uiLayer(uiLayer),
	backgroundLayer(backgroundLayer),
	scoreboard(10),
	healthbar(10, 60)
	{
	// Sets the initial score
	setScore(0);
}

void UIControl::populate(PlayerControl* playerControl){
	this->playerControl = playerControl;
}

void UIControl::update(float time_passed){
	background.update(time_passed);
}

void UIControl::nextBackground(){
	background.setFrame(background.getFrame()+1);
}

void UIControl::setScore(int newScore){
	score = newScore;
	scoreboard.displayScore(score);
}

void UIControl::draw() {
	background.draw(backgroundLayer);
	scoreboard.draw(uiLayer);
	healthbar.drawBar(uiLayer,
		playerControl->getLifes(),
		constants::START_LIFES
	);	
};
