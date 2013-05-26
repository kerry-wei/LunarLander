//
//  GameStateAbstract.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-25.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "GameStateAbstract.h"
#include "XInfo.h"
#include "GameSceneManager.h"
#include "GameObjectManager.h"
#include "TerrainManager.h"
#include "CollisionDetector.h"
#include "Spaceship.h"

GameStateAbstract::GameStateAbstract() {
    
}

GameStateAbstract::~GameStateAbstract() {
    
}

void GameStateAbstract::start() {
    
}

void GameStateAbstract::pause() {
    GameSceneManager* gameSceneManager = GameSceneManager::instance();
    gameSceneManager->showWindowTooSmallMessage();
}

void GameStateAbstract::resume(XConfigureEvent xce) {
    repositionPixmap(xce);
}

void GameStateAbstract::lose() {
    GameSceneManager* gameSceneManager = GameSceneManager::instance();
    gameSceneManager->showSpaceshipCrashScreen();
}

void GameStateAbstract::win() {
    GameSceneManager* gameSceneManager = GameSceneManager::instance();
    gameSceneManager->showLandingSucceedScreen();
}

void GameStateAbstract::startGame() {
    GameSceneManager* gameSceneManager = GameSceneManager::instance();
    GameObjectManager* gameObjManager = GameObjectManager::instance();
    TerrainManager* terrainManager = TerrainManager::instance();
    
    gameSceneManager->clearScreen();
    //gameSceneManager->removeWelcomeScreen();
    gameObjManager->resetSpaceship();
    Spaceship *spaceship = gameObjManager->getSpaceship();
    spaceship->moveToInitialPosition();
    spaceship->draw();
    
    terrainManager->initTerrain();
}

void GameStateAbstract::repositionPixmap(XConfigureEvent xce) {
    XInfo* xInfo = XInfo::instance(0, NULL);
    XClearWindow(xInfo->display, xInfo->window);
    
    // draw boundary
    XDrawRectangle(xInfo->display, xInfo->pixmap, xInfo->gc[0], 0, 0, xInfo->getPixmapWidth(), xInfo->getPixmapHeight());
    
    // re-position pixmap:
    xInfo->pixmapXOffset = (xce.width - xInfo->getPixmapWidth()) / 2;
    xInfo->pixmapYOffset = (xce.height - xInfo->getPixmapHeight()) / 2;
    
    XCopyArea(xInfo->display, xInfo->pixmap, xInfo->window, xInfo->gc[0],
              0, 0, xInfo->getPixmapWidth(), xInfo->getPixmapHeight(),  // region of pixmap to copy
              xInfo->pixmapXOffset, xInfo->pixmapYOffset); // position to put top left corner of pixmap in window
    XFlush(xInfo->display);
}

