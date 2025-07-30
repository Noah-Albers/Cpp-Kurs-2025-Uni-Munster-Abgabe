/*
 * Deathmessage.h
 *
 *  Created on: 30.07.2025
 *      Author: Noah
 */

#ifndef SRC_MODEL_DEATHMESSAGE_H_
#define SRC_MODEL_DEATHMESSAGE_H_

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "../view/Layer.hpp"


class Deathmessage {
public:
	Deathmessage(sf::Font& font);
	
	// Must be called after the font has been loaded
	void initialize();
	
	// Renders the death messages
	void draw(Layer& layer);
protected:
	sf::Text titleLabel;
	sf::Text subtitleLabel;
};

#endif /* SRC_MODEL_DEATHMESSAGE_H_ */
