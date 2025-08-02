
/*
 * CommonInterfaceTest.cpp
 *
 *  Created on: 02.08.2025
 *      Author: Noah
 */

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <gtest/gtest.h>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include "../../../src/model/interface/Deathmessage.h"
#include "../../../src/model/interface/Healthbar.h"
#include "../../../src/model/interface/Scoreboard.h"
#include "../../../src/model/interface/Shieldbar.h"
#include "../../../src/model/interface/Background.h"
#include "../../CommonMockClasses.cpp"
#include "../../../src/assets/AssetMappings.h"

class MockScoreboard : public Scoreboard {
public:
	MockScoreboard(const sf::Font& font) : Scoreboard(font) {}
	
	const sf::Text& getScoreLabel(){
		return scoreLabel;
	}
	
};

class CommonInterfaceTest : public ::testing::Test {
public:
	sf::RenderWindow win;
	MockLayer layer;
	sf::Font font;
	Deathmessage deathmsg;
	Healthbar hbar;
	MockScoreboard sboard;
	Shieldbar shield;
	Background bg;
	
	CommonInterfaceTest() :
		win(sf::VideoMode({10, 10}), "Dummy"),
		layer(win),
		deathmsg(font),
		hbar(10,10),
		sboard(font),
		shield(10,10)
	{
		// Loads the font
		if (!font.openFromFile(ASSETS_FONT_DEFAULT))
	        throw std::runtime_error("Failed to load Font");
	}
};

TEST_F(CommonInterfaceTest, deathmessage_draw) {
    deathmsg.initialize();
    
	EXPECT_CALL(layer, add_to_layer(testing::_))
		.Times(testing::AtLeast(1));
	
	deathmsg.draw(layer);
}

TEST_F(CommonInterfaceTest, healthbar_draw) {
	EXPECT_CALL(layer, add_to_layer(testing::_))
		.Times(testing::AtLeast(1));
	
	hbar.drawBar(layer, 5, 10);
}

TEST_F(CommonInterfaceTest, scoreboard_draw) {
	sboard.initialize(10);
	
	EXPECT_CALL(layer, add_to_layer(testing::_))
		.Times(testing::AtLeast(1));
	
	sboard.draw(layer);
}

TEST_F(CommonInterfaceTest, scoreboard_displayScore) {
	sboard.initialize(10);
	auto& lbl = sboard.getScoreLabel();
	
	sboard.displayScore(20);
	ASSERT_STREQ(lbl.getString().toAnsiString().c_str(), "20");
	sboard.displayScore(0);
	ASSERT_STREQ(lbl.getString().toAnsiString().c_str(), "0");
	sboard.displayScore(-99);
	ASSERT_STREQ(lbl.getString().toAnsiString().c_str(), "-99");
	sboard.displayScore(987);
	ASSERT_STREQ(lbl.getString().toAnsiString().c_str(), "987");	
}

TEST_F(CommonInterfaceTest, shieldbar_draw) {
	
	EXPECT_CALL(layer, add_to_layer(testing::_))
		.Times(testing::AtLeast(1));
	
	shield.drawBar(layer, 0);
}

TEST_F(CommonInterfaceTest, background_draw) {
	
	EXPECT_CALL(layer, add_to_layer(testing::_))
		.Times(testing::AtLeast(1));
	
	bg.draw(layer);
}