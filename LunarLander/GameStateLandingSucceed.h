//
//  GameStateLandingSucceed.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-25.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__GameStateLandingSucceed__
#define __LunarLander__GameStateLandingSucceed__

#include <iostream>
#include "GameStateAbstract.h"

class GameStateLandingSucceed : public GameStateAbstract {
public:
    GameStateLandingSucceed();
    ~GameStateLandingSucceed();
    static GameStateLandingSucceed* instance();
    
     void start();
    /*
     void pause();
     void resume();
     void stop();
     */
    
private:
    static GameStateLandingSucceed* gameStateLandingSucceed;
};

#endif /* defined(__LunarLander__GameStateLandingSucceed__) */
