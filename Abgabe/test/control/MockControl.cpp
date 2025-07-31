/**
 * MockControl.cpp
 * created on 31.07
 * author Olly
 */

#include "../../src/control/controls/AlienBulletControl.h"
#include "../../src/control/controls/AlienControl.h"
#include "../../src/control/controls/BulletControl.h"
#include "../../src/control/controls/LevelControl.h"
#include "../../src/control/controls/MeteorControl.h"
#include "../../src/control/controls/ParticleControl.h"
#include "../../src/control/controls/PlayerControl.h"
#include "../../src/control/controls/UIControl.h"

class MockControl {
    public:
    MockControl() :
        win(sf::VideoMode({10, 10}), "Dummy"),
        layer(win),
        layerbg(win),
        alienBulletControl(layer),
        alienControl(layer),
        bulletControl(layer),
        levelControl(),
        meteorControl(layer),
        particleControl(layer),
        playerControl(layer),
        uiControl(layer, layerbg)
        {
        alienBulletControl.populate(&playerControl);
	    alienControl.populate(&alienBulletControl, &levelControl, &playerControl);
	    bulletControl.populate(&alienControl, &meteorControl);
	    meteorControl.populate(&playerControl, &particleControl);
	    playerControl.populate(&bulletControl, &particleControl);
	    uiControl.populate(&playerControl);
        levelControl.populate(&alienControl, &uiControl);	
    };

    sf::RenderWindow win;
    Layer layer;
    Layer layerbg;
    AlienBulletControl  alienBulletControl;
    AlienControl        alienControl;
    BulletControl       bulletControl;
    LevelControl        levelControl;
    MeteorControl       meteorControl;
    ParticleControl     particleControl;
    PlayerControl       playerControl;
    UIControl           uiControl;
};
