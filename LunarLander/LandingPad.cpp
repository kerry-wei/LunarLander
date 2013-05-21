//
//  LandingPad.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-21.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "LandingPad.h"

LandingPad::LandingPad(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void LandingPad::draw() {
    XDrawRectangle(xInfo->display, xInfo->pixmap, xInfo->gc[0], x, y, width, height);
    // draw slash:
    int horizontalSpace = (width / 10);
    for (int i = 0; i < 10; i++) {
        XDrawLine(xInfo->display, xInfo->pixmap, xInfo->gc[0], i * space, y, (i + 1) * space, height);
    }
    
    // draw back-slash:
    for (int i = 0; i < 10; i++) {
        XDrawLine(xInfo->display, xInfo->pixmap, xInfo->gc[0], (i + 1) * space, y, i * space, height);
    }
}



LandingPad::~LandingPad() {
    
}

