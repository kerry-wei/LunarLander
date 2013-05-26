//
//  GameStateGameOver.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-25.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "GameStateGameOver.h"


GameStateGameOver* GameStateGameOver::gameOverState = NULL;

GameStateGameOver::GameStateGameOver() : GameStateAbstract() {
    
}

GameStateGameOver::~GameStateGameOver() {
    
}

GameStateGameOver* GameStateGameOver::instance() {
    if (!gameOverState) {
        gameOverState = new GameStateGameOver();
    }
    
    return gameOverState;
}


void GameStateGameOver::start() {
    startGame();
}

/*
void GameStateGameOver::pause() {
    
}

void GameStateGameOver::resume() {
    
}

void GameStateGameOver::stop() {
    
}
 */


