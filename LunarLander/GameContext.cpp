//
//  GameContext.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-25.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "GameContext.h"
#include "GameStateNotStarted.h"
#include "GameStateNotStartedSmallWindow.h"
#include "GameStateStarted.h"
#include "GameStatePausedSmallWindow.h"
#include "GameStateGameOver.h"
#include "GameStateGameOverSmallWindow.h"
#include "GameStateLandingSucceed.h"
#include "GameStateLandingSucceedSmallWindow.h"

GameContext* GameContext::gameContext = NULL;

GameContext* GameContext::instance() {
    if (!gameContext) {
        gameContext = new GameContext();
    }
    
    return gameContext;
}


GameContext::GameContext() {
    gameState = GameStateNotStarted::instance();
}

GameContext::~GameContext() {
    
}

bool GameContext::isGameStarted() {
    bool gameStarted = typeid(GameStateStarted) == typeid(*gameState);
    return gameStarted;
}

void GameContext::start() {
    if (!isGameStarted()) {
        gameState->start();
        if (typeid(GameStateNotStarted) == typeid(*gameState)) {
            gameState = GameStateStarted::instance();
        } else if (typeid(GameStateNotStartedSmallWindow) == typeid(*gameState)) {
            
        } else if (typeid(GameStateStarted) == typeid(*gameState)) {
            
        } else if (typeid(GameStatePausedSmallWindow) == typeid(*gameState)) {
            
        } else if (typeid(GameStateGameOver) == typeid(*gameState)) {
            gameState = GameStateStarted::instance();
        } else if (typeid(GameStateGameOverSmallWindow) == typeid(*gameState)) {
            
        } else if (typeid(GameStateLandingSucceed) == typeid(*gameState)) {
            gameState = GameStateStarted::instance();
        } else if (typeid(GameStateLandingSucceedSmallWindow) == typeid(*gameState)) {
            
        }
    }
    
    
}

void GameContext::pause() {
    gameState->pause();
    if (typeid(GameStateNotStarted) == typeid(*gameState)) {
        gameState = GameStateNotStartedSmallWindow::instance();
    } else if (typeid(GameStateNotStartedSmallWindow) == typeid(*gameState)) {
        
    } else if (typeid(GameStateStarted) == typeid(*gameState)) {
        gameState = GameStatePausedSmallWindow::instance();
    } else if (typeid(GameStatePausedSmallWindow) == typeid(*gameState)) {
        
    } else if (typeid(GameStateGameOver) == typeid(*gameState)) {
        gameState = GameStateGameOverSmallWindow::instance();
    } else if (typeid(GameStateGameOverSmallWindow) == typeid(*gameState)) {
        
    } else if (typeid(GameStateLandingSucceed) == typeid(*gameState)) {
        gameState = GameStateLandingSucceedSmallWindow::instance();
    } else if (typeid(GameStateLandingSucceedSmallWindow) == typeid(*gameState)) {
        
    }
}

void GameContext::resume(XConfigureEvent xce) {
    gameState->resume(xce);
    if (typeid(GameStateNotStarted) == typeid(*gameState)) {
        
    } else if (typeid(GameStateNotStartedSmallWindow) == typeid(*gameState)) {
        gameState = GameStateNotStarted::instance();
    } else if (typeid(GameStateStarted) == typeid(*gameState)) {
        
    } else if (typeid(GameStatePausedSmallWindow) == typeid(*gameState)) {
        gameState = GameStateStarted::instance();
    } else if (typeid(GameStateGameOver) == typeid(*gameState)) {
        
    } else if (typeid(GameStateGameOverSmallWindow) == typeid(*gameState)) {
        gameState = GameStateGameOver::instance();
    } else if (typeid(GameStateLandingSucceed) == typeid(*gameState)) {
        
    } else if (typeid(GameStateLandingSucceedSmallWindow) == typeid(*gameState)) {
        gameState = GameStateLandingSucceed::instance();
    }
}

void GameContext::lose() {
    gameState->lose();
    if (typeid(GameStateNotStarted) == typeid(*gameState)) {
        
    } else if (typeid(GameStateNotStartedSmallWindow) == typeid(*gameState)) {
        
    } else if (typeid(GameStateStarted) == typeid(*gameState)) {
        gameState = GameStateGameOver::instance();
    } else if (typeid(GameStatePausedSmallWindow) == typeid(*gameState)) {
        
    } else if (typeid(GameStateGameOver) == typeid(*gameState)) {
        
    } else if (typeid(GameStateGameOverSmallWindow) == typeid(*gameState)) {
        
    } else if (typeid(GameStateLandingSucceed) == typeid(*gameState)) {
        
    } else if (typeid(GameStateLandingSucceedSmallWindow) == typeid(*gameState)) {
        
    }
}

void GameContext::win() {
    gameState->win();
    if (typeid(GameStateNotStarted) == typeid(*gameState)) {
        
    } else if (typeid(GameStateNotStartedSmallWindow) == typeid(*gameState)) {
        
    } else if (typeid(GameStateStarted) == typeid(*gameState)) {
        gameState = GameStateLandingSucceed::instance();
    } else if (typeid(GameStatePausedSmallWindow) == typeid(*gameState)) {
        
    } else if (typeid(GameStateGameOver) == typeid(*gameState)) {
        
    } else if (typeid(GameStateGameOverSmallWindow) == typeid(*gameState)) {
        
    } else if (typeid(GameStateLandingSucceed) == typeid(*gameState)) {
        
    } else if (typeid(GameStateLandingSucceedSmallWindow) == typeid(*gameState)) {
        
    }
}



