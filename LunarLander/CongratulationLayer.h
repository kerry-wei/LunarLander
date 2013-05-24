//
//  CongratulationLayer.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-23.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__CongratulationLayer__
#define __LunarLander__CongratulationLayer__

#include <iostream>
#include <string>
#include "XInfo.h"

using namespace std;

class CongratulationLayer {
public:
    CongratulationLayer();
    ~CongratulationLayer();
    
    void drawCongratScreen();
    void clearCongratScreen();
    
private:
    XInfo *xInfo;
    
    string congratMsg;
    int congratMsgX;
    int congratMsgY;
    string restartMsg;
    int restartMsgX;
    int restartMsgY;
    string continueMsg;
    int continueMsgX;
    int continueMsgY;
    
    int spaceBetweenMsg;
};

#endif /* defined(__LunarLander__CongratulationLayer__) */
