//
//  main.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-11.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "XInfo.h"
#include "EventLoopManager.h"
#include "GameObjectManager.h"
#include "GameSceneManager.h"
#include "GameState.h"

using namespace std;


int main(int argc, char** argv) {
    GameObjectManager::init();
    GameState::init();
    
    GameSceneManager *gameSceneManager = GameSceneManager::instance();
    gameSceneManager->showWelcomeScreen();
    
    
    // tmp: create spaceship here
    GameObjectManager *gameObjManager = GameObjectManager::instance();
    Spaceship *spaceship = gameObjManager->getSpaceship();
    spaceship->draw();
    // end
    
    EventLoopManager eventLoopManager = EventLoopManager();
    eventLoopManager.eventloop();
    
}

