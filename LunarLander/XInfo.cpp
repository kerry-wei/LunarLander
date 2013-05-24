//
//  XInfo.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-11.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "XInfo.h"
#include <iostream>
#include <stdlib.h>
using namespace std;


XInfo* XInfo::xInfo = NULL;

XInfo* XInfo::instance(int argc, char *argv[]) {
    if (!xInfo) {
        xInfo = new XInfo(argc, argv);
    }
    
    return xInfo;
}

XInfo::XInfo (int argc, char *argv[]) {
    XSizeHints hints;
    unsigned long white, black;
    
    /*
     * Display opening uses the DISPLAY	environment variable.
     * It can go wrong if DISPLAY isn't set, or you don't have permission.
     */
    this->display = XOpenDisplay( "" );
    XAutoRepeatOn(this->display);
    if (!this->display)	{
        cerr << "Can't open display." << endl;
        exit(0);
    }
    
    /*
     * Find out some things about the display you're using.
     */
    this->screen = DefaultScreen( this->display );
    desiredWidth = 800;
    desiredHeight = 600;
    pixmapXOffset = 0;
    pixmapYOffset = 0;
    white = XWhitePixel( this->display, this->screen );
    black = XBlackPixel( this->display, this->screen );
    
    hints.x = 100;
    hints.y = 100;
    hints.width = desiredWidth;
    hints.height = desiredHeight;
    hints.flags = PPosition | PSize;
    
    this->window = XCreateSimpleWindow(
                                       this->display,				// display where window appears
                                       DefaultRootWindow(this->display), // window's parent in window tree
                                       hints.x, hints.y,			// upper left corner location
                                       hints.width, hints.height,	// size of the window
                                       5,						// width of window's border
                                       black,						// window border colour
                                       white                    // window background colour
                                       );
    
    XSetStandardProperties(
                           this->display,		// display containing the window
                           this->window,		// window whose properties are set
                           "Lunar Lander",			// window's title
                           "",				// icon's title
                           None,				// pixmap for the icon
                           argv,
                           argc,			// applications command line args
                           &hints          // size hints for the window
                           );
    
    // black
    gc[1] = XCreateGC(display, window, 0, 0);
	XSetForeground(display, gc[1], BlackPixel(display, screen));
	XSetBackground(display, gc[1], WhitePixel(display, screen));
	XSetFillStyle(display, gc[1], FillSolid);
	XSetLineAttributes(display, gc[1], 1, LineSolid, CapButt, JoinRound);
    
    // white
    gc[0] = XCreateGC(display, window, 0, 0);
	XSetForeground(display, gc[0], WhitePixel(display, screen));
	XSetBackground(display, gc[0], BlackPixel(display, screen));
	XSetFillStyle(display, gc[0], FillSolid);
	XSetLineAttributes(display, gc[0], 1, LineSolid, CapButt, JoinRound);
    
    int depth = DefaultDepth(display, DefaultScreen(display));
    pixmap = XCreatePixmap(display, window, hints.width, hints.height, depth);
    
    /*
     * Put the window on the screen.
     */
    XMapRaised( this->display, this->window );
    
    XFlush(this->display);
}

bool XInfo::windowSizeIsEnough() {
    int windowWidth = getWindowWidth();
    int windowHeight = getWindowHeight();
    return (windowWidth >= desiredWidth && windowHeight >= desiredHeight);
}

int XInfo::getPixmapWidth() {
    return desiredWidth;
}

int XInfo::getPixmapHeight() {
    return desiredHeight;
}

int XInfo::getWindowWidth() {
    XWindowAttributes windowAttr;
    XGetWindowAttributes(xInfo->display, xInfo->window, &windowAttr);
    return windowAttr.width;
}

int XInfo::getWindowHeight() {
    XWindowAttributes windowAttr;
    XGetWindowAttributes(xInfo->display, xInfo->window, &windowAttr);
    return windowAttr.height;
}

