//
//  TerrainGenerator.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-14.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__TerrainGenerator__
#define __LunarLander__TerrainGenerator__

#include <iostream>
#include <X11/Xlib.h>
#include <vector>
#include "TerrainPoint.h"
#include "XInfo.h"
#include "PathDefinition.h"
#include "TerrainSegment.h"

using namespace std;


class TerrainGenerator {
public:
    static TerrainGenerator* instance();
    TerrainGenerator();
    ~TerrainGenerator();
    
    vector<TerrainSegment*>* createInitialTerrain();
    bool canShiftTerrainToRight();
    bool shouldCreateLeftTerrain();
    bool shouldCreateRightTerrain();
    
    vector<TerrainSegment*>* getActiveTerrain();
    vector<TerrainSegment*>* getLeftShiftedTerrain(double deltaX);
    vector<TerrainSegment*>* getRightShiftedTerrain(double deltaX);
    
private:
    static TerrainGenerator* terrainGenerator;
    XInfo *xInfo;
    int minFlyingSpace;
    
    int windowWidth;
    int windowHeight;
    
    int baseNumOfPath;
    int maxNumOfPath;
    int numOfTerrainSegment;
    
    int baseLandingPadCount;
    int maxLandingPadCount;
    int landingPadCount;
    
    vector<TerrainSegment*>* activeTerrain;
    vector<TerrainSegment*>* leftInactiveTerrain;
    vector<TerrainSegment*>* rightInactiveTerrain;
    
    void shiftTerrain(vector<TerrainSegment*>* terrain, double deltaX);
    vector<PathSpec> generatePathSpecs(int numOfPathSpec);
    
    void addTerrainSegments(vector<TerrainSegment*>* terrain);
    
};

#endif /* defined(__LunarLander__TerrainGenerator__) */
