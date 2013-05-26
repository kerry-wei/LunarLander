//
//  GameStateGameOver.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-25.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__GameStateGameOver__
#define __LunarLander__GameStateGameOver__

#include <iostream>
#include "GameStateAbstract.h"

class GameStateGameOver : public GameStateAbstract {
public:
    GameStateGameOver();
    ~GameStateGameOver();
    static GameStateGameOver* instance();
    
    void start();
    /*
    void pause();
    void resume();
    void stop();
     */
    
private:
    static GameStateGameOver* gameOverState;
};

#endif /* defined(__LunarLander__GameStateGameOver__) */
