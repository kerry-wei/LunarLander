//
//  WelcomeLayer.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-19.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include <X11/Xlib.h>
#include <sstream>
#include "WelcomeLayer.h"
#include "XInfo.h"

using namespace std;


WelcomeLayer::WelcomeLayer() {
    xInfo = XInfo::instance(0, NULL);
    spaceBetweenMsg = 25;
    
    scoreLabelXPos = 15;
    scoreLabelYPos = 15;
    scoreLabelWidth = 0;
    scoreLabelHeight = 0;
    
    timeLabelXPos = scoreLabelXPos;
    timeLabelYPos = scoreLabelYPos + spaceBetweenMsg;
    timeLabelWidth = 0;
    timeLabelHeight = 0;
    
    fuelLabelXPos = scoreLabelXPos;
    fuelLabelYPos = timeLabelYPos + spaceBetweenMsg;
    fuelLabelWidth = 0;
    fuelLabelHeight = 0;
    
    altitudeLabelXPos = 630;
    altitudeLabelYPos = scoreLabelYPos;
    altitudeLabelWidth = 0;
    altitudeLabelHeight = 0;
    
    xSpeedLabelXPos = altitudeLabelXPos;
    xSpeedLabelYPos = altitudeLabelYPos + spaceBetweenMsg;
    xSpeedLabelWidth = 0;
    xSpeedLabelHeight = 0;
    
    ySpeedLabelXPos = altitudeLabelXPos;
    ySpeedLabelYPos = xSpeedLabelYPos + spaceBetweenMsg;
    ySpeedLabelWidth = 0;
    ySpeedLabelHeight = 0;
}


void WelcomeLayer::drawWelcomeScreen() {
    GC gc = xInfo->gc[0];
    
    int pixmapWidth = xInfo->getPixmapWidth();
    int pixmapHeight = xInfo->getPixmapHeight();
    
    // font size: 8, 10, 12, 14, 18, 24
    XFontStruct *font = XLoadQueryFont(xInfo->display, "12x24");
    XSetFont(xInfo->display, gc, font->fid);
    
    string beginGame = "Press SPACE to start";
    int labelWidth = XTextWidth(font, beginGame.c_str(), (int)beginGame.length());
    int xPosition = pixmapWidth / 2 - labelWidth / 2;
    int yPosition = pixmapHeight / 2 - 100;
    XDrawImageString(xInfo->display, xInfo->pixmap, gc, xPosition, yPosition, beginGame.c_str(), (int)beginGame.length());
    
    string quitGame = "Press Q to quit";
    labelWidth = XTextWidth(font, quitGame.c_str(), (int)quitGame.length());
    xPosition = pixmapWidth / 2 - labelWidth / 2;
    yPosition = pixmapHeight / 2 + spaceBetweenMsg - 86;
    XDrawImageString(xInfo->display, xInfo->pixmap, gc, xPosition, yPosition, quitGame.c_str(), (int)quitGame.length());
    
}

void WelcomeLayer::clearWelcomeScreen() {
    XFillRectangle(xInfo->display, xInfo->pixmap, xInfo->gc[1], 0, 0, xInfo->getPixmapWidth(), xInfo->getPixmapHeight());
    XFreePixmap(xInfo->display, xInfo->pixmap);
    int depth = DefaultDepth(xInfo->display, DefaultScreen(xInfo->display));
    xInfo->pixmap = XCreatePixmap(xInfo->display, xInfo->window, xInfo->getPixmapWidth(), xInfo->getPixmapHeight(), depth);
    
    XClearWindow(xInfo->display, xInfo->window);
    updateGameInfo(0, 0.0, 0.0, 0.0, 0.0, 0.0);
}

void WelcomeLayer::updateGameInfo(int score, double time, double fuel, double altitude, double xSpeed, double ySpeed) {
    //cout << "score: " << score << ", time: " << time << ", fuel: " << fuel << ", altitude: " << altitude << ", xSpeed: " << xSpeed << ", ySpeed:" << ySpeed << endl;
    GC gc = xInfo->gc[0];
    GC blackGC = xInfo->gc[1];
    XFontStruct *font = XLoadQueryFont(xInfo->display, "*x10");
    XSetFont(xInfo->display, xInfo->gc[0], font->fid);
    string numToString;
    ostringstream convert;
    int direction_return;
    int font_ascent_return, font_descent_return;
    XCharStruct overall_return;
    
    // left side:
    //XClearArea(xInfo->display, xInfo->window, scoreLabelXPos, scoreLabelYPos - scoreLabelHeight, scoreLabelWidth, scoreLabelHeight, false);
    XFillRectangle(xInfo->display, xInfo->pixmap, blackGC, scoreLabelXPos, scoreLabelYPos - scoreLabelHeight, scoreLabelWidth, scoreLabelHeight);
    string scoreMsg = "SCORE: ";
    convert.clear();
    convert.str("");
    convert << score;
    numToString = convert.str();
    scoreMsg += numToString;
    XTextExtents(font, scoreMsg.c_str(), (int)scoreMsg.length(), &direction_return, &font_ascent_return, &font_descent_return, &overall_return);
    scoreLabelWidth = XTextWidth(font, scoreMsg.c_str(), (int)scoreMsg.length());
    scoreLabelHeight = font_ascent_return + font_descent_return;
    XDrawImageString(xInfo->display, xInfo->pixmap, gc, scoreLabelXPos, scoreLabelYPos, scoreMsg.c_str(), (int)scoreMsg.length());
    
    //XClearArea(xInfo->display, xInfo->window, timeLabelXPos, timeLabelYPos - timeLabelHeight, timeLabelWidth, timeLabelHeight, false);
    XFillRectangle(xInfo->display, xInfo->pixmap, blackGC, timeLabelXPos, timeLabelYPos - timeLabelHeight, timeLabelWidth, timeLabelHeight);
    string timeMsg = "TIME: ";
    convert.clear();
    convert.str("");
    convert << time;
    numToString = convert.str();
    timeMsg += numToString;
    XTextExtents(font, timeMsg.c_str(), (int)timeMsg.length(), &direction_return, &font_ascent_return, &font_descent_return, &overall_return);
    timeLabelHeight = font_ascent_return + font_descent_return;
    timeLabelWidth = XTextWidth(font, timeMsg.c_str(), (int)timeMsg.length());
    XDrawImageString(xInfo->display, xInfo->pixmap, gc, timeLabelXPos, timeLabelYPos, timeMsg.c_str(), (int)timeMsg.length());
    
    //XClearArea(xInfo->display, xInfo->window, fuelLabelXPos, fuelLabelYPos - fuelLabelHeight, fuelLabelWidth, fuelLabelHeight, false);
    XFillRectangle(xInfo->display, xInfo->pixmap, blackGC, fuelLabelXPos, fuelLabelYPos - fuelLabelHeight, fuelLabelWidth, fuelLabelHeight);
    string fuelMsg = "FUEL: ";
    convert.clear();
    convert.str("");
    convert << fuel;
    numToString = convert.str();
    fuelMsg += numToString;
    XTextExtents(font, fuelMsg.c_str(), (int)fuelMsg.length(), &direction_return, &font_ascent_return, &font_descent_return, &overall_return);
    fuelLabelHeight = font_ascent_return + font_descent_return;
    fuelLabelWidth = XTextWidth(font, fuelMsg.c_str(), (int)fuelMsg.length());
    XDrawImageString(xInfo->display, xInfo->pixmap, gc, fuelLabelXPos, fuelLabelYPos, fuelMsg.c_str(), (int)fuelMsg.length());
    
    
    // right side:
    //XClearArea(xInfo->display, xInfo->window, altitudeLabelXPos, altitudeLabelYPos - altitudeLabelHeight, altitudeLabelWidth, altitudeLabelHeight, false);
    XFillRectangle(xInfo->display, xInfo->pixmap, blackGC, altitudeLabelXPos, altitudeLabelYPos - altitudeLabelHeight, altitudeLabelWidth, altitudeLabelHeight);
    string altitudeMsg = "ALTITUDE: ";
    convert.clear();
    convert.str("");
    convert << altitude;
    numToString = convert.str();
    altitudeMsg += numToString;
    XTextExtents(font, altitudeMsg.c_str(), (int)altitudeMsg.length(), &direction_return, &font_ascent_return, &font_descent_return, &overall_return);
    altitudeLabelHeight = font_ascent_return + font_descent_return;
    altitudeLabelWidth = XTextWidth(font, altitudeMsg.c_str(), (int)altitudeMsg.length());
    XDrawImageString(xInfo->display, xInfo->pixmap, gc, altitudeLabelXPos, altitudeLabelYPos, altitudeMsg.c_str(), (int)altitudeMsg.length());
    
    //XClearArea(xInfo->display, xInfo->window, xSpeedLabelXPos, xSpeedLabelYPos - xSpeedLabelHeight, xSpeedLabelWidth + 30, xSpeedLabelHeight, false);
    XFillRectangle(xInfo->display, xInfo->pixmap, blackGC, xSpeedLabelXPos, xSpeedLabelYPos - xSpeedLabelHeight, xSpeedLabelWidth + 10, xSpeedLabelHeight + 1);
    string horizontalSpeedMsg = "HORIZONTAL SPEED: ";
    convert.clear();
    convert.str("");
    convert << xSpeed;
    numToString = convert.str();
    horizontalSpeedMsg += numToString;
    XTextExtents(font, horizontalSpeedMsg.c_str(), (int)horizontalSpeedMsg.length(), &direction_return, &font_ascent_return, &font_descent_return, &overall_return);
    xSpeedLabelHeight = font_ascent_return + font_descent_return;
    xSpeedLabelWidth = XTextWidth(font, horizontalSpeedMsg.c_str(), (int)horizontalSpeedMsg.length());
    XDrawImageString(xInfo->display, xInfo->pixmap, gc, xSpeedLabelXPos, xSpeedLabelYPos, horizontalSpeedMsg.c_str(), (int)horizontalSpeedMsg.length());
    
    //XClearArea(xInfo->display, xInfo->window, ySpeedLabelXPos, ySpeedLabelYPos - ySpeedLabelHeight, ySpeedLabelWidth, ySpeedLabelHeight, false);
    XFillRectangle(xInfo->display, xInfo->pixmap, blackGC, ySpeedLabelXPos, ySpeedLabelYPos - ySpeedLabelHeight, ySpeedLabelWidth, ySpeedLabelHeight);
    string verticalSpeedMsg = "VERTICAL SPEED: ";
    convert.clear();
    convert.str("");
    convert << ySpeed;
    numToString = convert.str();
    verticalSpeedMsg += numToString;
    XTextExtents(font, verticalSpeedMsg.c_str(), (int)verticalSpeedMsg.length(), &direction_return, &font_ascent_return, &font_descent_return, &overall_return);
    ySpeedLabelHeight = font_ascent_return + font_descent_return;
    ySpeedLabelWidth = XTextWidth(font, verticalSpeedMsg.c_str(), (int)verticalSpeedMsg.length());
    XDrawImageString(xInfo->display, xInfo->pixmap, gc, ySpeedLabelXPos, ySpeedLabelYPos, verticalSpeedMsg.c_str(), (int)verticalSpeedMsg.length());
    
}


WelcomeLayer::~WelcomeLayer() {
    
}


