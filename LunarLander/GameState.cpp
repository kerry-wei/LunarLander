//
//  GameState.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-16.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "GameState.h"

using namespace std;

GameState* GameState::gameState = NULL;

GameState* GameState::instance() {
    if (!gameState) {
        gameState = new GameState();
    }
    return gameState;
}

void GameState::init() {
    if (!gameState) {
        gameState = new GameState();
    }
}

GameState::GameState() {
    gameStarted = false;
}

GameState::~GameState() {
    
}

bool GameState::isGameStarted() {
    return gameStarted;
}

void GameState::setGameStarted(bool started) {
    gameStarted = started;
}


















