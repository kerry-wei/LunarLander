//
//  EventLoopManager.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-11.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__EventLoopManager__
#define __LunarLander__EventLoopManager__

#include <iostream>
#include "XInfo.h"
#include "GameSceneManager.h"
#include "GameState.h"
#include "GameObjectManager.h"
#include "TerrainManager.h"
#include "CollisionDetector.h"
#include "GameContext.h"

using namespace std;

class EventLoopManager {
public:
    EventLoopManager();
    void startGameLoop();
    
private:
    int FPS;
    XInfo* xInfo;
    GameSceneManager* gameSceneManager;
    GameObjectManager* gameObjManager;
    TerrainManager* terrainManager;
    //GameState* gameState;
    CollisionDetector* collisionDetector;
    GameContext* gameContext;
    
    void handleQuitGame();
    void handleStartGame();
    void handleSpaceshipCrash();
    void handleLandingSucceed();
    void handleResize(XInfo* xInfo, XEvent &event);
};


#endif /* defined(__LunarLander__EventLoopManager__) */