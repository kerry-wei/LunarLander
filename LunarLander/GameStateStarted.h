//
//  GameStateStarted.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-25.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__GameStateStarted__
#define __LunarLander__GameStateStarted__

#include <iostream>
#include "GameStateAbstract.h"

class GameStateStarted : public GameStateAbstract {
public:
    GameStateStarted();
    ~GameStateStarted();
    static GameStateStarted* instance();
    
    void start();
    /*
    void pause();
    void resume();
    void stop();
     */
    
private:
    static GameStateStarted* gameStarted;
};

#endif /* defined(__LunarLander__GameStateStarted__) */
