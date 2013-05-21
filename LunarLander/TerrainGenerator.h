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

using namespace std;

class TerrainGenerator {
public:
    static TerrainGenerator* instance();
    TerrainGenerator();
    ~TerrainGenerator();
    
    vector<TerrainPoint*>* createInitialTerrain();
    bool canShiftTerrainToRight();
    bool shouldCreateLeftTerrain();
    bool shouldCreateRightTerrain();
    
    vector<TerrainPoint*>* getActiveTerrain();
    vector<TerrainPoint*>* getLeftShiftedTerrain(double deltaX);
    vector<TerrainPoint*>* getRightShiftedTerrain(double deltaX);
    
private:
    static TerrainGenerator* terrainGenerator;
    XInfo *xInfo;
    int minFlyingSpace;
    
    int windowWidth;
    int windowHeight;
    
    int baseNumOfPath;
    int maxNumOfPath;
    int numOfPath;
    
    int baseLandingPadCount;
    int maxLandingPadCount;
    int landingPadCount;
    
    vector<TerrainPoint*>* activeTerrain;
    vector<TerrainPoint*>* leftInactiveTerrain;
    vector<TerrainPoint*>* rightInactiveTerrain;
    
    vector<TerrainPoint*>* generateSubPath(TerrainPoint startPoint, TerrainPoint endPoint, int numOfPoints);
    void shiftTerrain(vector<TerrainPoint*> *terrain, double deltaX);
    void addTerrain(vector<TerrainPoint*> *terrain, int offSetToPreviousForFirstPoint);
    
};

#endif /* defined(__LunarLander__TerrainGenerator__) */
