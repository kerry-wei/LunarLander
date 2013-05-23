//
//  EventLoopManager.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-11.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__EventLoopManager__
#define __LunarLander__EventLoopManager__

#include <iostream>
#include "XInfo.h"

using namespace std;

class EventLoopManager {
public:
    EventLoopManager();
    void eventloop();
    
private:
    int FPS;
    XInfo* xInfo;
    void handleQuitGame();
    void handleStartGame();
    void handleResize(XInfo* xInfo, XEvent &event);
    void repositionPixmap(XConfigureEvent xce);
};


#endif /* defined(__LunarLander__EventLoopManager__) */