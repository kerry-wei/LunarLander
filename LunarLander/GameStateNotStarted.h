//
//  GameStateNotStarted.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-25.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__GameStateNotStarted__
#define __LunarLander__GameStateNotStarted__

#include <iostream>
#include "GameStateAbstract.h"

class GameStateNotStarted : public GameStateAbstract {
public:
    GameStateNotStarted();
    ~GameStateNotStarted();
    static GameStateNotStarted* instance();
    
    void start();
    /*
    void pause();
    void resume();
    void stop();
     */
    
private:
    static GameStateNotStarted* gameStateNotStarted;
};

#endif /* defined(__LunarLander__GameStateNotStarted__) */
