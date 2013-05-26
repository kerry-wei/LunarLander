//
//  GameStateNotStarted.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-25.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "GameStateNotStarted.h"



GameStateNotStarted* GameStateNotStarted::gameStateNotStarted = NULL;

GameStateNotStarted::GameStateNotStarted() : GameStateAbstract() {
    
}

GameStateNotStarted::~GameStateNotStarted() {
    
}

GameStateNotStarted* GameStateNotStarted::instance() {
    if (!gameStateNotStarted) {
        gameStateNotStarted = new GameStateNotStarted();
    }
    
    return gameStateNotStarted;
}


void GameStateNotStarted::start() {
    startGame();
}

/*
void GameStateNotStarted::pause() {
    
}

void GameStateNotStarted::resume() {
    
}

void GameStateNotStarted::stop() {
    
}
 */


