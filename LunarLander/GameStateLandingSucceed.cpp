//
//  GameStateLandingSucceed.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-25.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "GameStateLandingSucceed.h"

GameStateLandingSucceed* GameStateLandingSucceed::gameStateLandingSucceed = NULL;

GameStateLandingSucceed::GameStateLandingSucceed() : GameStateAbstract() {
    
}

GameStateLandingSucceed::~GameStateLandingSucceed() {
    
}

GameStateLandingSucceed* GameStateLandingSucceed::instance() {
    if (!gameStateLandingSucceed) {
        gameStateLandingSucceed = new GameStateLandingSucceed();
    }
    
    return gameStateLandingSucceed;
}

void GameStateLandingSucceed::start() {
    startGame();
}

/*
 void GameStateLandingSucceed::pause() {
 
 }
 
 void GameStateLandingSucceed::resume() {
 
 }
 
 void GameStateLandingSucceed::stop() {
 
 }
 */


