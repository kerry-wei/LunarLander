//
//  XInfo.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-11.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__XInfo__
#define __LunarLander__XInfo__

#include <X11/Xlib.h>
#include <X11/Xutil.h>

class XInfo {
public:
    static XInfo* instance(int argc, char *argv[]);
    XInfo(int argc, char *argv[]);
    
    bool windowSizeIsEnough();
    int getPixmapWidth();
    int getPixmapHeight();
    int getWindowWidth();
    int getWindowHeight();
    
    Display	 *display;
	int		 screen;
	Window	 window;
    Pixmap	pixmap;
    int pixmapXOffset;
    int pixmapYOffset;
    GC gc[2];
    
private:
    static XInfo *xInfo;
    int desiredWidth;
    int desiredHeight;
};

#endif /* defined(__LunarLander__XInfo__) */
