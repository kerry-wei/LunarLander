//
//  TerrainPoint.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-18.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__TerrainPoint__
#define __LunarLander__TerrainPoint__

#include <iostream>
#include <X11/Xlib.h>

class TerrainPoint {
public:
    
    
    XPoint getXPoint();
    
    void setPosition(int x, int y);
    void setXCoordinate(int x);
    void setYCoordinate(int y);
    int getXCoordinate();
    int getYCoordinate();
    
    void setXOffsetToPrevious(int offset);
    void setXOffsetToNext(int offset);
    int getXOffsetToPrevious();
    int getXOffsetToNext();
    
    TerrainPoint();
    TerrainPoint(int x, int y);
    TerrainPoint(int x, int y, int xOffsetToPrevious, int xOffsetToNext);
    TerrainPoint(const TerrainPoint &point);
    
    static bool isUpwardPath(TerrainPoint p1, TerrainPoint p2);
    
private:
    XPoint xPoint;
    int xOffsetToPrevious;
    int xOffsetToNext;
};

#endif /* defined(__LunarLander__TerrainPoint__) */
