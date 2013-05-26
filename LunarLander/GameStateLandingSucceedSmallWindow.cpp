//
//  GameStateLandingSucceedSmallWindow.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-25.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "GameStateLandingSucceedSmallWindow.h"


GameStateLandingSucceedSmallWindow* GameStateLandingSucceedSmallWindow::landingSucceedSmallWindow = NULL;

GameStateLandingSucceedSmallWindow::GameStateLandingSucceedSmallWindow() : GameStateAbstract() {
    
}

GameStateLandingSucceedSmallWindow::~GameStateLandingSucceedSmallWindow() {
    
}

GameStateLandingSucceedSmallWindow* GameStateLandingSucceedSmallWindow::instance() {
    if (!landingSucceedSmallWindow) {
        landingSucceedSmallWindow = new GameStateLandingSucceedSmallWindow();
    }
    
    return landingSucceedSmallWindow;
}


void GameStateLandingSucceedSmallWindow::start() {
    
}

/*
 void GameStateGameOverSmallWindow::pause() {
 
 }
 
 void GameStateGameOverSmallWindow::resume() {
 
 }
 
 void GameStateGameOverSmallWindow::stop() {
 
 }
 */


