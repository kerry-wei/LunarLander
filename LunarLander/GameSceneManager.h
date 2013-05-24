//
//  GameSceneManager.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-16.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__GameSceneManager__
#define __LunarLander__GameSceneManager__

#include <iostream>
#include "WelcomeLayer.h"
#include "GameOverLayer.h"
#include "CongratulationLayer.h"

class GameSceneManager {
public:
    static GameSceneManager* instance();
    
    GameSceneManager();
    ~GameSceneManager();
    
    void clearScreen();
    void showWelcomeScreen();
    void removeWelcomeScreen();
    void showSpaceshipCrashScreen();
    void showLandingSucceedScreen();
    void showWindowTooSmallMessage();
    void updateGameInfo(int score, double time, double fuel, double altitude, double xSpeed, double ySpeed);
    
    
private:
    static GameSceneManager* gameSceneManager;
    
    XInfo *xInfo;
    WelcomeLayer welcomeLayer;
    GameOverLayer gameOverLayer;
    CongratulationLayer congratLayer;
    
    void copyPixmapToWindow();
};

#endif /* defined(__LunarLander__GameSceneManager__) */

