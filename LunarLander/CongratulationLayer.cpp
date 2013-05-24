//
//  CongratulationLayer.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-23.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "CongratulationLayer.h"


CongratulationLayer::CongratulationLayer() {
    xInfo = XInfo::instance(0, NULL);
    congratMsg = "CONGRATULATIONS! :)";
    restartMsg = "Press SPACE to Restart";
    continueMsg = "Press ENTER to Continue the Adventure";
    
    spaceBetweenMsg = 50;
    int pixmapWidth = xInfo->getPixmapWidth();
    int pixmapHeight = xInfo->getPixmapHeight();
    XFontStruct *font = XLoadQueryFont(xInfo->display, "12x24");
    
    int labelWidth = XTextWidth(font, congratMsg.c_str(), (int)congratMsg.length());
    congratMsgX = pixmapWidth / 2 - labelWidth / 2;
    congratMsgY = pixmapHeight / 2 - 160;
    
    labelWidth = XTextWidth(font, restartMsg.c_str(), (int)restartMsg.length());
    restartMsgX = pixmapWidth / 2 - labelWidth / 2;
    restartMsgY = congratMsgY + spaceBetweenMsg;
    
    labelWidth = XTextWidth(font, continueMsg.c_str(), (int)continueMsg.length());
    continueMsgX = pixmapWidth / 2 - labelWidth / 2;
    continueMsgY = restartMsgY + spaceBetweenMsg;
}

CongratulationLayer::~CongratulationLayer() {
    
}

void CongratulationLayer::drawCongratScreen() {
    GC gc = xInfo->gc[0];
    XFontStruct *font = XLoadQueryFont(xInfo->display, "12x24");
    XSetFont(xInfo->display, gc, font->fid);
    
    XDrawImageString(xInfo->display, xInfo->pixmap, gc, congratMsgX, congratMsgY, congratMsg.c_str(), (int)congratMsg.length());
    XDrawImageString(xInfo->display, xInfo->pixmap, gc, restartMsgX, restartMsgY, restartMsg.c_str(), (int)restartMsg.length());
    XDrawImageString(xInfo->display, xInfo->pixmap, gc, continueMsgX, continueMsgY, continueMsg.c_str(), (int)continueMsg.length());
}

void CongratulationLayer::clearCongratScreen() {
    
}


