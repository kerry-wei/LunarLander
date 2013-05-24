//
//  GameOverLayer.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-23.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "GameOverLayer.h"


GameOverLayer::GameOverLayer() {
    xInfo = XInfo::instance(0, NULL);
    crashMsg = "Spaceship Crashes... :(";
    restartMsg = "Press SPACE to Restart";
    spaceBetweenMsg = 50;
    int pixmapWidth = xInfo->getPixmapWidth();
    int pixmapHeight = xInfo->getPixmapHeight();
    XFontStruct *font = XLoadQueryFont(xInfo->display, "12x24");
    int labelWidth = XTextWidth(font, crashMsg.c_str(), (int)crashMsg.length());
    crashMsgX = pixmapWidth / 2 - labelWidth / 2;
    crashMsgY = pixmapHeight / 2 - 100;
    
    labelWidth = XTextWidth(font, restartMsg.c_str(), (int)restartMsg.length());
    restartMsgX = pixmapWidth / 2 - labelWidth / 2;
    restartMsgY = crashMsgY + spaceBetweenMsg;
    
    
}

GameOverLayer::~GameOverLayer() {
    
}

void GameOverLayer::drawGameOverScreen() {
    GC gc = xInfo->gc[0];
    XFontStruct *font = XLoadQueryFont(xInfo->display, "12x24");
    XSetFont(xInfo->display, gc, font->fid);
    
    XDrawImageString(xInfo->display, xInfo->pixmap, gc, crashMsgX, crashMsgY, crashMsg.c_str(), (int)crashMsg.length());
    XDrawImageString(xInfo->display, xInfo->pixmap, gc, restartMsgX, restartMsgY, restartMsg.c_str(), (int)restartMsg.length());
}

void GameOverLayer::clearGameOverScreen() {
    
}




