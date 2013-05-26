//
//  GameStateGameOverSmallWindow.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-25.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "GameStateGameOverSmallWindow.h"


GameStateGameOverSmallWindow* GameStateGameOverSmallWindow::gameOverSmallWindowState = NULL;

GameStateGameOverSmallWindow::GameStateGameOverSmallWindow() : GameStateAbstract() {
    
}

GameStateGameOverSmallWindow::~GameStateGameOverSmallWindow() {
    
}

GameStateGameOverSmallWindow* GameStateGameOverSmallWindow::instance() {
    if (!gameOverSmallWindowState) {
        gameOverSmallWindowState = new GameStateGameOverSmallWindow();
    }
    
    return gameOverSmallWindowState;
}

void GameStateGameOverSmallWindow::start() {
    
}

/*
void GameStateGameOverSmallWindow::pause() {
    
}

void GameStateGameOverSmallWindow::resume() {
    
}

void GameStateGameOverSmallWindow::stop() {
    
}
 */


