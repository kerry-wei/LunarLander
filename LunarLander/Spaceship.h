//
//  Spaceship.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-15.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__Spaceship__
#define __LunarLander__Spaceship__

#include <iostream>
#include <vector>
#include <X11/Xlib.h>
#include "DrawableObject.h"
#include "XInfo.h"

using namespace std;

class Spaceship : public DrawableObject {
public:
    Spaceship();
    Spaceship(int x, int y);
    void reset();
    
    void move(int deltaX, int deltaY);
    void moveToInitialPosition();
    void draw();
    void playAnimation();
    void timerUpdate();
    
    bool isMovingLeft();
    bool isMovingRight();
    
    double getXSpeed();
    double getYSpeed();
    void setXSpeed(double delta);
    void setYSpeed(double delta);
    
    
private:
    double xSpeed;
    double ySpeed;
    
    double xSpeedLimit;
    double ySpeedLimit;
    
    int xLeftLimit;
    int xRightLimit;
    
    int initialX;
    int initialY;
    
    int animationFrameCount;
    int animationFrameIndex;
    vector<Pixmap> *animations;
};

#endif /* defined(__LunarLander__Spaceship__) */
