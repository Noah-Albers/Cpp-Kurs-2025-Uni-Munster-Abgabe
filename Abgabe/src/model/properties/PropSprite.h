/*
 * PropSprite.h
 *
 *  Created on: 26.07.2025
 *      Author: Noah
 */

#ifndef SRC_MODEL_PROPERTIES_PROPSPRITE_H_
#define SRC_MODEL_PROPERTIES_PROPSPRITE_H_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

class PropSprite {
public:
	PropSprite(const std::filesystem::path& filename, const int size_x, const int size_y, const float scale = 1, const bool centerOrigin = false);
	virtual ~PropSprite();
	
	// Detects whether the current object collides with another
	bool isCollidingWith(PropSprite& object);

	// Sets the texture to the given frame
	void setFrame(int index);
	
	// Returns how many frames exist in the current texture
	int getFrameAmount();
	
	// Getters/Setters
	sf::Sprite getSprite();
	int getFrame();

protected:
    // Texture and sprite for the object
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif /* SRC_MODEL_PROPERTIES_PROPSPRITE_H_ */
