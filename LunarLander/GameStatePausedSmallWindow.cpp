//
//  GameStatePausedSmallWindow.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-25.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "GameStatePausedSmallWindow.h"



GameStatePausedSmallWindow* GameStatePausedSmallWindow::pausedSmallWindow = NULL;

GameStatePausedSmallWindow::GameStatePausedSmallWindow() : GameStateAbstract() {
    
}

GameStatePausedSmallWindow::~GameStatePausedSmallWindow() {
    
}

GameStatePausedSmallWindow* GameStatePausedSmallWindow::instance() {
    if (!pausedSmallWindow) {
        pausedSmallWindow = new GameStatePausedSmallWindow();
    }
    
    return pausedSmallWindow;
}

void GameStatePausedSmallWindow::start() {
    
}

/*
void GameStatePausedSmallWindow::pause() {
    
}

void GameStatePausedSmallWindow::resume() {
    
}

void GameStatePausedSmallWindow::stop() {
    
}
 */


