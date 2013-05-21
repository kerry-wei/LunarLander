//
//  GameObjectManager.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-16.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "GameObjectManager.h"


GameObjectManager* GameObjectManager::gameObjectManager = NULL;

GameObjectManager::GameObjectManager() {
    spaceship = new Spaceship(-100, -100);
    cout << "game obj created" << endl;
}

void GameObjectManager::init() {
    if (!GameObjectManager::gameObjectManager) {
        GameObjectManager::gameObjectManager = new GameObjectManager();
    }
}

GameObjectManager* GameObjectManager::instance() {
    if (!GameObjectManager::gameObjectManager) {
        GameObjectManager::gameObjectManager = new GameObjectManager();
        return gameObjectManager;
    } else {
        return gameObjectManager;
    }
}


Spaceship* GameObjectManager::getSpaceship() {
    return spaceship;
}


void GameObjectManager:: timerUpdate() {
    spaceship->timerUpdate();
}






GameObjectManager::~GameObjectManager() {
}



