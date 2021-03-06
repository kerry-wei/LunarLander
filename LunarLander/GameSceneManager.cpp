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
    xInfo = XInfo::instance(0, NULL);
    welcomeLayer = WelcomeLayer();
    gameOverLayer = GameOverLayer();
    congratLayer = CongratulationLayer();
}

void GameSceneManager::clearScreen() {
    XFillRectangle(xInfo->display, xInfo->pixmap, xInfo->gc[1], 0, 0, xInfo->getPixmapWidth(), xInfo->getPixmapHeight());
    XFlush(xInfo->display);
    XFreePixmap(xInfo->display, xInfo->pixmap);
    int depth = DefaultDepth(xInfo->display, DefaultScreen(xInfo->display));
    xInfo->pixmap = XCreatePixmap(xInfo->display, xInfo->window, xInfo->getPixmapWidth(), xInfo->getPixmapHeight(), depth);
}

void GameSceneManager::showWelcomeScreen() {
    XFillRectangle(xInfo->display, xInfo->pixmap, xInfo->gc[1], 0, 0, xInfo->getPixmapWidth(), xInfo->getPixmapHeight());
    welcomeLayer.updateGameInfo(0, 0.0, 0.0, 0.0, 0.0, 0.0);
    welcomeLayer.drawWelcomeScreen();
    copyPixmapToWindow();
}

void GameSceneManager::removeWelcomeScreen() {
    welcomeLayer.clearWelcomeScreen();
}

void GameSceneManager::showSpaceshipCrashScreen() {
    clearScreen();
    
    welcomeLayer.updateGameInfo(0, 0.0, 0.0, 0.0, 0.0, 0.0);
    gameOverLayer.drawGameOverScreen();
    
    copyPixmapToWindow();
}

void GameSceneManager::showLandingSucceedScreen() {
    clearScreen();
    
    welcomeLayer.updateGameInfo(0, 0.0, 0.0, 0.0, 0.0, 0.0);
    congratLayer.drawCongratScreen();
    
    copyPixmapToWindow();
}

void GameSceneManager::showWindowTooSmallMessage() {
    XInfo *xInfo = XInfo::instance(0, NULL);
    XWindowAttributes windowAttr;
    XGetWindowAttributes(xInfo->display, xInfo->window, &windowAttr);
    GC gc = xInfo->gc[1];
    
    // font size: 8, 10, 12, 14, 18, 24
    XFontStruct *font = XLoadQueryFont(xInfo->display, "12x24");
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

void GameSceneManager::copyPixmapToWindow() {
    GC gc = xInfo->gc[0];
    Display* display = xInfo->display;
    Drawable from = xInfo->pixmap;
    Drawable to = xInfo->window;
    int width = xInfo->getPixmapWidth();
    int height = xInfo->getPixmapHeight();
    int xOffset = xInfo->pixmapXOffset;
    int yOffset = xInfo->pixmapYOffset;
    XCopyArea(display, from, to, gc, 0, 0, width, height, xOffset, yOffset);
    XFlush(xInfo->display);
}

GameSceneManager::~GameSceneManager() {
    
}



