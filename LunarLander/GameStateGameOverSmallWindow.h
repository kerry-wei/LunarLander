//
//  GameStateGameOverSmallWindow.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-25.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__GameStateGameOverSmallWindow__
#define __LunarLander__GameStateGameOverSmallWindow__

#include <iostream>
#include "GameStateAbstract.h"

class GameStateGameOverSmallWindow : public GameStateAbstract {
public:
    GameStateGameOverSmallWindow();
    ~GameStateGameOverSmallWindow();
    static GameStateGameOverSmallWindow* instance();
    
    void start();
    /*
    void pause();
    void resume();
    void stop();
     */
    
private:
    static GameStateGameOverSmallWindow* gameOverSmallWindowState;
};

#endif /* defined(__LunarLander__GameStateGameOverSmallWindow__) */
