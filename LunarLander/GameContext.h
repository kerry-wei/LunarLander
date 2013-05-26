//
//  GameContext.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-25.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__GameContext__
#define __LunarLander__GameContext__

#include <iostream>
#include "GameStateAbstract.h"

class GameContext {
public:
    static GameContext* instance();
    GameContext();
    ~GameContext();
    
    bool isGameStarted();
    
    void start();
    void pause();
    void resume(XConfigureEvent xce);
    void lose();
    void win();
    
private:
    static GameContext *gameContext;
    GameStateAbstract* gameState;
};

#endif /* defined(__LunarLander__GameContext__) */
