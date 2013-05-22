//
//  TerrainSegment.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-21.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__TerrainSegment__
#define __LunarLander__TerrainSegment__

#include <iostream>
#include <vector>
#include "TerrainPoint.h"
#include "PathDefinition.h"
#include "XInfo.h"

using namespace std;


class TerrainSegment {
public:
    TerrainSegment(TerrainPoint p1, TerrainPoint p2, PathSpec pathSpec, int numOfPoints);
    ~TerrainSegment();
    bool isOffScreen();
    bool isCompletelyInsideScreen();
    void shiftTerrainSegment(double deltaX);
    void updateRightmostPosition(int rightmostX);
    void updateLeftmostPosition(int leftmostX);
    int getLeftmostXCoordinate();
    int getRightmostXCoordinate();
    void drawSegment();
    void clearSegment();
    void draw(unsigned long foreground, unsigned long background);
    void printSegment();
    
private:
    //TerrainPoint p1;
    //TerrainPoint p2;
    PathSpec pathSpec;
    XInfo *xInfo;
    //int numOfPoints;
    
    vector<TerrainPoint> segmentPath;
    
    void generateSegment(TerrainPoint startPoint, TerrainPoint endPoint, PathSpec spec, int numOfPoints);
    void updateXOffsets();
    
    void addTerrain(int offSetToPreviousForFirstPoint);
};

#endif /* defined(__LunarLander__TerrainSegment__) */
