//
//  GameStateLandingSucceedSmallWindow.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-25.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__GameStateLandingSucceedSmallWindow__
#define __LunarLander__GameStateLandingSucceedSmallWindow__

#include <iostream>
#include "GameStateAbstract.h"

class GameStateLandingSucceedSmallWindow : public GameStateAbstract {
public:
    GameStateLandingSucceedSmallWindow();
    ~GameStateLandingSucceedSmallWindow();
    static GameStateLandingSucceedSmallWindow* instance();
    
    void start();
    /*
     void pause();
     void resume();
     void stop();
     */
    
private:
    static GameStateLandingSucceedSmallWindow* landingSucceedSmallWindow;
};


#endif /* defined(__LunarLander__GameStateLandingSucceedSmallWindow__) */
