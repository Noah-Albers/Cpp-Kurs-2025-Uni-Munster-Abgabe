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

// For Sprites, it holds the path and the comma separated x/y size of a single frame,
// followed by a multiplier that will scale the final image when its loaded.
// For static Sprites it will be the full size of the picture
// Format: 								<Path>									<x>		<y>		<scale>
#define ASSETS_SPRITE_PLAYER 			"assets/sprites/player_default.png",	32, 	28,		2.6
#define ASSETS_SPRITE_PLAYER_SHIELD		"assets/sprites/player_shield.png",		34,		30,		2.6
#define ASSETS_SPRITE_PLAYER_DEATH 		"assets/sprites/player_death.png",		64, 	64,		2.6
#define ASSETS_SPRITE_PLAYER_BULLET 	"assets/sprites/player_bullet.png",		5, 		10, 	2.4

#define ASSETS_SPRITE_ALIEN				"assets/sprites/alien_default.png",		24,		22,		2.3
#define ASSETS_SPRITE_ALIEN_SHIELD 		"assets/sprites/alien_shield.png",		26,		24,		2.3
#define ASSETS_SPRITE_ALIEN_BULLET 		"assets/sprites/alien_bullet.png",		18,		38,		1.5
#define ASSETS_SPRITE_METEOR 			"assets/sprites/meteor.png",			38,		33,		1.4
#define ASSETS_SPRITE_METEOR_EXPLOSION 	"assets/sprites/meteor_explosion.png",	90, 	96,		1.4
#define ASSETS_SPRITE_BACKGROUND 		"assets/sprites/background.png",		720,	1080,	1
#define ASSETS_SPRITE_HEALTH 			"assets/sprites/health.png",			7, 		7,		6
#define ASSETS_SPRITE_SHIELD_BAR		"assets/sprites/player_shieldbar.png",	42,		5,		4.5
#define ASSETS_EXPLOSION	 			"assets/sprites/explosion.png",			80, 	48,		3


#endif /* SRC_ASSETS_ASSETMAPPINGS_H_ */
