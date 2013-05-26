//
//  GameStatePausedSmallWindow.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-25.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__GameStatePausedSmallWindow__
#define __LunarLander__GameStatePausedSmallWindow__

#include <iostream>
#include "GameStateAbstract.h"

class GameStatePausedSmallWindow : public GameStateAbstract {
public:
    GameStatePausedSmallWindow();
    ~GameStatePausedSmallWindow();
    static GameStatePausedSmallWindow* instance();
    
    void start();
    /*
    void pause();
    void resume();
    void stop();
     */
    
private:
    static GameStatePausedSmallWindow* pausedSmallWindow;
};

#endif /* defined(__LunarLander__GameStatePausedSmallWindow__) */
