//
//  DrawableObject.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-15.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "DrawableObject.h"
#include "XInfo.h"
#include <X11/Xlib.h>

DrawableObject::DrawableObject() {
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
    xInfo = XInfo::instance(0, NULL);
}

DrawableObject::DrawableObject(int x, int y) {
    this->x = x;
    this->y = y;
    xInfo = XInfo::instance(0, NULL);
}

DrawableObject::DrawableObject(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    xInfo = XInfo::instance(0, NULL);
}

void DrawableObject::move(int deltaX, int deltaY) {
    this->x += deltaX;
    this->y += deltaY;
}

int DrawableObject::getXPosition() {
    return x;
}

int DrawableObject::getYPosition() {
    return y;
}

void DrawableObject::draw() {
    
}

// DOTO: careful when collision happens. maybe re-draw self with white color is better,
// but still it might wipe out part of the terrain
void DrawableObject::clearDrawing() {
    /*
    GC gc = XCreateGC(xInfo.display, xInfo.window, 0, 0);
	XSetForeground(xInfo.display, gc, WhitePixel(xInfo.display, xInfo.screen));
	XSetBackground(xInfo.display, gc, WhitePixel(xInfo.display, xInfo.screen));
	XSetFillStyle(xInfo.display, gc, FillSolid);
	XSetLineAttributes(xInfo.display, gc, 7, LineSolid, CapRound, JoinMiter);
     */
    
    XFillRectangle(xInfo->display, xInfo->pixmap, xInfo->gc[1], x - 1, y - 1, width + 2, height + 2);
    
    //XClearArea(xInfo->display, xInfo->window, x - 1, y - 1, width + 2, height + 2, false);
    
}


