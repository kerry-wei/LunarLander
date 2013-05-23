//
//  GameSceneManager.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-16.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include <sstream>
#include "GameSceneManager.h"
#include "XInfo.h"

using namespace std;

GameSceneManager* GameSceneManager::gameSceneManager = NULL;

GameSceneManager* GameSceneManager::instance() {
    if (!gameSceneManager) {
        gameSceneManager = new GameSceneManager();
    }
    
    return gameSceneManager;
}


GameSceneManager::GameSceneManager() {
    welcomeLayer = WelcomeLayer();
}

void GameSceneManager::showWelcomeScreen() {
    XInfo *xInfo = XInfo::instance(0, NULL);
    XFillRectangle(xInfo->display, xInfo->pixmap, xInfo->gc[1], 0, 0, xInfo->getPixmapWidth(), xInfo->getPixmapHeight());
    welcomeLayer.updateGameInfo(0, 0.0, 0.0, 0.0, 0.0, 0.0);
    welcomeLayer.drawWelcomeScreen();
    XCopyArea(xInfo->display, xInfo->pixmap, xInfo->window, xInfo->gc[0],
              0, 0, xInfo->getPixmapWidth(), xInfo->getPixmapHeight(),  // region of pixmap to copy
              xInfo->pixmapXOffset, xInfo->pixmapYOffset); // position to put top left corner of pixmap in window
    XFlush(xInfo->display);
}

void GameSceneManager::removeWelcomeScreen() {
    welcomeLayer.clearWelcomeScreen();
}

void GameSceneManager::showWindowTooSmallMessage() {
    XInfo *xInfo = XInfo::instance(0, NULL);
    XWindowAttributes windowAttr;
    XGetWindowAttributes(xInfo->display, xInfo->window, &windowAttr);
    GC gc = XCreateGC(xInfo->display, xInfo->window, 0, 0);
    XSetBackground(xInfo->display, gc, WhitePixel(xInfo->display, xInfo->screen));
    XSetForeground(xInfo->display, gc, BlackPixel(xInfo->display, xInfo->screen));
    
    // font size: 8, 10, 12, 14, 18, 24
    XFontStruct *font = XLoadQueryFont(xInfo->display, "-*-helvetica-*-24-*");
    XSetFont(xInfo->display, gc, font->fid);
    
    string beginGame = "Window Size Too Small";
    int labelWidth = XTextWidth(font, beginGame.c_str(), (int)beginGame.length());
    int xPosition = windowAttr.width / 2 - labelWidth / 2;
    int yPosition = windowAttr.height / 2;
    XDrawImageString(xInfo->display, xInfo->window, gc, xPosition, yPosition, beginGame.c_str(), (int)beginGame.length());
}

void GameSceneManager::updateGameInfo(int score, double time, double fuel, double altitude, double xSpeed, double ySpeed) {
    welcomeLayer.updateGameInfo(score, time, fuel, altitude, xSpeed, ySpeed);
}


GameSceneManager::~GameSceneManager() {
    
}






