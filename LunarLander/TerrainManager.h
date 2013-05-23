//
//  TerrainManager.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-17.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__TerrainManager__
#define __LunarLander__TerrainManager__

#include <iostream>
#include "TerrainGenerator.h"
#include "TerrainRenderer.h"
#include "Spaceship.h"

class TerrainManager {
public:
    static TerrainManager* instance();
    TerrainManager();
    ~TerrainManager();
    void resetTerrain();
    bool shouldUpdateTerrain(double x, double y);
    void updateTerrainBasedOnSpaceshipPosition(Spaceship *spaceship, double deltaX, double deltaY);
    
private:
    static TerrainManager* terrainManager;
    int xLeftLimit;
    int xRightLimit;
    TerrainGenerator *terrainGenerator;
    TerrainRenderer *terrainRenderer;
    
    void updateLeftTerrain(double deltaX);
    void updateRightTerrain(double deltaX);
};

#endif /* defined(__LunarLander__TerrainManager__) */
