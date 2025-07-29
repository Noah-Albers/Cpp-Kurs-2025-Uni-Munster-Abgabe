/*
 * AssetMappings.h
 *
 *  Created on: 28.07.2025
 *      Author: Noah
 *
 * Holds the mappings between asset file paths and useable "variable" names
 */

#ifndef SRC_ASSETS_ASSETMAPPINGS_H_
#define SRC_ASSETS_ASSETMAPPINGS_H_


// For Fonts, it just holds the path to the font
#define ASSETS_FONT_DEFAULT "assets/fonts/DejaVuSansMono.ttf"

// For Sprites, it holds the path and the comma separated x/y size of a single from
// followed by a muliplyer that will scale the final image when its loaded
// For static Sprites it will be the full size of the picture
// Format: 								<Path>									<x>		<y>		<scale>
#define ASSETS_SPRITE_ALIEN_BULLET 		"assets/sprites/Alien_Bullet.png",		18,		38,		1
#define ASSETS_SPRITE_ALIEN				"assets/sprites/alien_default.png",		24,		22,		1.5
#define ASSETS_SPRITE_ALIEN_SHIELD 		"assets/sprites/Alien_Shield.png",		26,		24,		1.5
#define ASSETS_SPRITE_METEOR 			"assets/sprites/Asteroid.png",			38,		33,		1
#define ASSETS_SPRITE_METEOR_EXPLOSION 	"assets/sprites/Asteroid_Explosion.png",90, 	96,		2
#define ASSETS_SPRITE_BACKGROUND 		"assets/sprites/background.png",		720,	1080,	1
#define ASSETS_SPRITE_PLAYER_BULLET 	"assets/sprites/bullet_default.png",	5, 		18, 	1
#define ASSETS_SPRITE_HEALTH 			"assets/sprites/health.png",			7, 		7,		6
#define ASSETS_SPRITE_PLAYER_DEATH 		"assets/sprites/player_death.png",		64, 	64,		2
#define ASSETS_SPRITE_PLAYER 			"assets/sprites/player_default.png",	32, 	28,		2


#endif /* SRC_ASSETS_ASSETMAPPINGS_H_ */
