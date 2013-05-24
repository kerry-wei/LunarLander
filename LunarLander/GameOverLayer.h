//
//  GameOverLayer.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-23.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__GameOverLayer__
#define __LunarLander__GameOverLayer__

#include <iostream>
#include "XInfo.h"
#include <string>

using namespace std;

class GameOverLayer {
public:
    GameOverLayer();
    ~GameOverLayer();
    
    void drawGameOverScreen();
    void clearGameOverScreen();
    
private:
    XInfo *xInfo;
    
    string crashMsg;
    int crashMsgX;
    int crashMsgY;
    string restartMsg;
    int restartMsgX;
    int restartMsgY;
    
    int spaceBetweenMsg;
};

#endif /* defined(__LunarLander__GameOverLayer__) */
