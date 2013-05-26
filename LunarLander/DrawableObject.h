//
//  DrawableObject.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-15.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__DrawableObject__
#define __LunarLander__DrawableObject__

#include <iostream>
#include "XInfo.h"

class DrawableObject {
public:
    DrawableObject();
    DrawableObject(double x, double y);
    DrawableObject(double x, double y, int width, int height);
    void move(double deltaX, double deltaY);
    double getXPosition();
    double getYPosition();
    int getWidth();
    int getHeight();
    virtual void draw();
    
    void clearDrawing();
    
protected:
    XInfo *xInfo;
    
    double x;
    double y;
    int width;
    int height;
};

#endif /* defined(__LunarLander__DrawableObject__) */
