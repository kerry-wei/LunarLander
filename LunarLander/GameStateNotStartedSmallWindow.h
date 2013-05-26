//
//  GameStateNotStartedSmallWinow.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-25.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__GameStateNotStartedSmallWindow__
#define __LunarLander__GameStateNotStartedSmallWindow__

#include <iostream>
#include "GameStateAbstract.h"

class GameStateNotStartedSmallWindow : public GameStateAbstract {
public:
    GameStateNotStartedSmallWindow();
    ~GameStateNotStartedSmallWindow();
    static GameStateNotStartedSmallWindow* instance();
    
    void start();
    /*
    void pause();
    void resume();
    void stop();
     */
    
private:
    static GameStateNotStartedSmallWindow* notStartedSmallWindow;
};

#endif /* defined(__LunarLander__GameStateNotStartedSmallWinow__) */
