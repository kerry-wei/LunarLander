//
//  TerrainManager.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-17.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "TerrainManager.h"
#include <X11/Xlib.h>
#include <vector>
#include "Utilities.h"

using namespace std;

TerrainManager* TerrainManager::terrainManager = NULL;

TerrainManager* TerrainManager::instance() {
    if (!terrainManager) {
        terrainManager = new TerrainManager();
    }
    
    return terrainManager;
}

TerrainManager::TerrainManager() {
    xLeftLimit = 200;
    xRightLimit = 500;
    terrainGenerator = TerrainGenerator::instance();
    terrainRenderer = TerrainRenderer::instance();
}

/*
int TerrainManager::getXLeftLimit() {
    return xLeftLimit;
}
 */

bool TerrainManager::shouldUpdateTerrain(double x, double y) {
    if ((x <= xLeftLimit && terrainGenerator->canShiftTerrainToRight()) || x >= xRightLimit) {
        return true;
    } else {
        return false;
    }
}

void TerrainManager::updateTerrainBasedOnSpaceshipPosition(Spaceship *spaceship, double deltaX, double deltaY) {
    int x = spaceship->getXPosition();
    if (x + deltaX <= xLeftLimit) {
        updateLeftTerrain(deltaX);
    } else if (x + deltaX >= xRightLimit) {
        updateRightTerrain(deltaX);
    } else {
        Utilities::reportError("ERROR: TerrainManager doesn't know how to update terrain");
    }
}

void TerrainManager::updateLeftTerrain(double deltaX) {
    if (deltaX > 0) {
        Utilities::reportError("deltaX should be negative");
    }
    
    vector<TerrainPoint*>* currentTerrain = terrainGenerator->getActiveTerrain();
    terrainRenderer->clearTerrain(currentTerrain);
    
    vector<TerrainPoint*> *activeTerrain = terrainGenerator->getRightShiftedTerrain(deltaX);
    
    // debug:
    cout << "going to print shifted active terrain:" << endl;
    Utilities::printTerrainPoint(activeTerrain);
    cout << endl << endl;
    // end
    
    terrainRenderer->drawTerrain(activeTerrain);
}

void TerrainManager::updateRightTerrain(double deltaX) {
    vector<TerrainPoint*>* currentTerrain = terrainGenerator->getActiveTerrain();
    terrainRenderer->clearTerrain(currentTerrain);
    
    vector<TerrainPoint*> *activeTerrain = terrainGenerator->getLeftShiftedTerrain(deltaX);
    terrainRenderer->drawTerrain(activeTerrain);
}

TerrainManager::~TerrainManager() {
    
}








