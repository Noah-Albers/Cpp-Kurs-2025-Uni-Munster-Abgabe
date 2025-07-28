/*
 * MeteorController.cpp
 *
 *  Created on: 27.07.2025
 *      Author: Alica
 */
#include <iostream>
#include <ostream>
#include <cstdlib>
#include "MeteorControl.h"
#include "../model/Constants.hpp"
#include "Game.hpp"

MeteorControl::MeteorControl(Layer &layer) : layer(layer) {}
MeteorControl::~MeteorControl() {}

void MeteorControl::update(float time_passed){
	// Moves Meteors forward and removes any that went out of screen
	for (auto meteors_it = meteors.begin(); meteors_it != meteors.end(); ) {
		bool erased = false;

        
		auto& player = Game::getInstance().getPlayerControl().getPlayer();

		
			if(meteors_it->collision(player)){
        		Game::getInstance().getPlayerControl().damage();
                meteors_it = meteors.erase(meteors_it);
        		erased = true;
                
        		break;
    		}
		
            if(meteors_it->getPosition().y > constants::GAME_HEIGHT+20){
			    meteors_it = meteors.erase(meteors_it);
                erased = true;
                
                break;

            }

            if (!erased){
                meteors_it->updatePosition();
                ++ meteors_it;	
                
            }
		
		
	}	



    //count the time that passed since last Meteor spawn
    timer += time_passed;

    // when wanted time passed, spawn new meteor at random x coordinate and reset time
    if (timer>time_between_meteors){
        spawnMeteorAt(rand() % constants::GAME_WIDTH,-20);
        timer = 0;
    }
    
}

void MeteorControl::draw(){
	for(auto it = meteors.begin(); it != meteors.end(); it++)
		layer.add_to_layer(it->getSprite());
}

void MeteorControl::spawnMeteorAt(const int x, const int y) {
	meteors.emplace_back(x,y);

}

