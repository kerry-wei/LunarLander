//
//  WelcomeLayer.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-19.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__WelcomeLayer__
#define __LunarLander__WelcomeLayer__

#include <iostream>
#include "XInfo.h"

class WelcomeLayer {
public:
    WelcomeLayer();
    
    void drawWelcomeScreen();
    void clearWelcomeScreen();
    void updateGameInfo(int score, double time, double fuel, double altitude, double xSpeed, double ySpeed);
    
    ~WelcomeLayer();
private:
    XInfo *xInfo;
    
    // left side:
    int scoreLabelXPos;
    int scoreLabelYPos;
    int scoreLabelWidth;
    int scoreLabelHeight;
    
    int timeLabelXPos;
    int timeLabelYPos;
    int timeLabelWidth;
    int timeLabelHeight;
    
    int fuelLabelXPos;
    int fuelLabelYPos;
    int fuelLabelWidth;
    int fuelLabelHeight;
    
    // right side:
    int altitudeLabelXPos;
    int altitudeLabelYPos;
    int altitudeLabelWidth;
    int altitudeLabelHeight;
    
    int xSpeedLabelXPos;
    int xSpeedLabelYPos;
    int xSpeedLabelWidth;
    int xSpeedLabelHeight;
    
    int ySpeedLabelXPos;
    int ySpeedLabelYPos;
    int ySpeedLabelWidth;
    int ySpeedLabelHeight;
    
    int spaceBetweenMsg;
    
};

#endif /* defined(__LunarLander__WelcomeLayer__) */

