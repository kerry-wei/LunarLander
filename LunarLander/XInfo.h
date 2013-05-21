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
    
    int getWindowWidth();
    int getWindowHeight();
    
    XInfo(int argc, char *argv[]);
    Display	 *display;
	int		 screen;
	Window	 window;
    Pixmap	pixmap;
    int desiredWidth;
    int desiredHeight;
    int pixmapXOffset;
    int pixmapYOffset;
    GC gc[2];
    
private:
    static XInfo *xInfo;
    
};

#endif /* defined(__LunarLander__XInfo__) */
