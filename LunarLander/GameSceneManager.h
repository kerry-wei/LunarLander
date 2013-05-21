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

class GameSceneManager {
public:
    static GameSceneManager* instance();
    
    GameSceneManager();
    ~GameSceneManager();
    
    void showWelcomeScreen();
    void removeWelcomeScreen();
    void showWindowTooSmallMessage();
    void updateGameInfo(int score, double time, double fuel, double altitude, double xSpeed, double ySpeed);
    
    
private:
    static GameSceneManager* gameSceneManager;
    WelcomeLayer welcomeLayer;
};

#endif /* defined(__LunarLander__GameSceneManager__) */

