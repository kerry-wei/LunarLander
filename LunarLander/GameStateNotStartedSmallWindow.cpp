//
//  GameStateNotStartedSmallWinow.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-25.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "GameStateNotStartedSmallWindow.h"


GameStateNotStartedSmallWindow* GameStateNotStartedSmallWindow::notStartedSmallWindow = NULL;

GameStateNotStartedSmallWindow::GameStateNotStartedSmallWindow() : GameStateAbstract() {
    
}

GameStateNotStartedSmallWindow::~GameStateNotStartedSmallWindow() {
    
}

GameStateNotStartedSmallWindow* GameStateNotStartedSmallWindow::instance() {
    if (!notStartedSmallWindow) {
        notStartedSmallWindow = new GameStateNotStartedSmallWindow();
    }
    
    return notStartedSmallWindow;
}

void GameStateNotStartedSmallWindow::start() {
    
}

/*
void GameStateNotStartedSmallWinow::pause() {
    
}

void GameStateNotStartedSmallWinow::resume() {
    
}

void GameStateNotStartedSmallWinow::stop() {
    
}
 */

