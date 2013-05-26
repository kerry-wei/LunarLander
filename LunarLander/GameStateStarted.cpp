//
//  GameStateStarted.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-25.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "GameStateStarted.h"
#include "GameSceneManager.h"

GameStateStarted* GameStateStarted::gameStarted = NULL;

GameStateStarted::GameStateStarted() : GameStateAbstract() {
    
}

GameStateStarted::~GameStateStarted() {
    
}

GameStateStarted* GameStateStarted::instance() {
    if (!gameStarted) {
        gameStarted = new GameStateStarted();
    }
    
    return gameStarted;
}


void GameStateStarted::start() {
    
}

/*
void GameStateStarted::pause() {
}

void GameStateStarted::resume() {
    
}

void GameStateStarted::stop() {
    
}
 */
