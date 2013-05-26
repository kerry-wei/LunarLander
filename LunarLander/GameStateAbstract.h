//
//  GameStateAbstract.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-25.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__GameStateAbstract__
#define __LunarLander__GameStateAbstract__

#include <iostream>
#include <X11/Xlib.h>

class GameStateAbstract {
public:
    GameStateAbstract();
    ~GameStateAbstract();
    
    virtual void start();
    virtual void pause();
    virtual void resume(XConfigureEvent xce);
    virtual void lose();
    virtual void win();
    
protected:
    void startGame();
    void repositionPixmap(XConfigureEvent xce);
};

#endif /* defined(__LunarLander__GameStateAbstract__) */
