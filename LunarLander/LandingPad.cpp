//
//  LandingPad.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-21.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "LandingPad.h"

using namespace std;


LandingPad::LandingPad(TerrainPoint p1, TerrainPoint p2, PathSpec pathSpce) :TerrainSegment(p1, p2, pathSpce, 2) {
    //this->p1 = p1;
    //this->p2 = p2;
    /*
    x = p1->getXCoordinate();
    y = p1->getYCoordinate();
    width = abs(p2->getXCoordinate() - p1->getXCoordinate());
    height = 20;
    xInfo = XInfo::instance(0, NULL);
     */
    this->height = 20;
}

void LandingPad::drawSegment() {
    TerrainPoint p1 = segmentPath.at(0);
    TerrainPoint p2 = segmentPath.at(1);
    
    int x1 = p1.getXCoordinate();
    int y1 = p1.getYCoordinate();
    int x2 = p2.getXCoordinate();
    int y2 = p2.getYCoordinate();
    
    XDrawLine(xInfo->display, xInfo->pixmap, xInfo->gc[0], x1, y1, x2, y2);
    
    drawLandingPad();
}

void LandingPad::clearSegment() {
    clearDrawing();
}

void LandingPad::drawLandingPad() {
    XDrawRectangle(xInfo->display, xInfo->pixmap, xInfo->gc[0], x, y, width, height);
    // draw slash:
    int horizontalSpace = (width / 10);
    for (int i = 0; i < 10; i++) {
        XDrawLine(xInfo->display, xInfo->pixmap, xInfo->gc[0], x + i * horizontalSpace, y, x + (i + 1) * horizontalSpace, y + height);
    }
    
    // draw back-slash:
    for (int i = 0; i < 10; i++) {
        XDrawLine(xInfo->display, xInfo->pixmap, xInfo->gc[0], x + (i + 1) * horizontalSpace, y, x + i * horizontalSpace, y + height);
    }
}



LandingPad::~LandingPad() {
    
}

