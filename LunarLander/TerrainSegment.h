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
#include "DrawableObject.h"
#include "XInfo.h"

using namespace std;


class TerrainSegment : public DrawableObject {
public:
    TerrainSegment(TerrainPoint p1, TerrainPoint p2, PathSpec pathSpec, int numOfPoints);
    ~TerrainSegment();
    bool isOffScreen();
    bool isCompletelyInsideScreen();
    void shiftTerrainSegment(double deltaX);
    void updateRightmostPosition(TerrainPoint point);
    void updateLeftmostPosition(TerrainPoint point);
    void updateSegmentPosition();
    vector<TerrainPoint> getBoundaryPoints(int x);
    TerrainPoint getLeftmostPoint();
    TerrainPoint getRightmostPoint();
    int getLeftmostXCoordinate();
    int getRightmostXCoordinate();
    virtual void drawSegment();
    virtual void clearSegment();
    
    void printSegment();
    
protected:
    PathSpec pathSpec;
    vector<TerrainPoint> segmentPath;
    void draw(unsigned long foreground, unsigned long background);
    void generateSegment(TerrainPoint startPoint, TerrainPoint endPoint, PathSpec spec, int numOfPoints);
    void updateXOffsets();
    
    void addTerrain(int offSetToPreviousForFirstPoint);
};

#endif /* defined(__LunarLander__TerrainSegment__) */
