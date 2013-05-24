//
//  CollisionDetector.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-21.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include <typeinfo>
#include "CollisionDetector.h"
#include "LandingPad.h"
#include "TerrainPoint.h"
#include "GameObjectManager.h"
#include "TerrainGenerator.h"

using namespace std;

CollisionDetector* CollisionDetector::collisionDetector = NULL;

CollisionDetector* CollisionDetector::instance() {
    if (!collisionDetector) {
        collisionDetector = new CollisionDetector();
    }
    
    return collisionDetector;
}

CollisionDetector::CollisionDetector() {
    terrainManager = TerrainManager::instance();
    landingSpeedLimit = 3.0;
}

bool CollisionDetector::spaceshipCrashWillHappen() {
    GameObjectManager *gameObjManager = GameObjectManager::instance();
    Spaceship *spaceship = gameObjManager->getSpaceship();
    TerrainGenerator* terrainGenerator = TerrainGenerator::instance();
    TerrainSegment* segment = terrainGenerator->getTerrainSegmentBasedOnX(spaceship->getXPosition());
    
    if (typeid(LandingPad) == typeid(*segment)) {
        return spaceship->getYSpeed() > landingSpeedLimit;
    } else {
        return collisionHappens(spaceship, segment);
    }
    
}

bool CollisionDetector::isLandingSuccessful() {
    GameObjectManager *gameObjManager = GameObjectManager::instance();
    Spaceship *spaceship = gameObjManager->getSpaceship();
    TerrainGenerator* terrainGenerator = TerrainGenerator::instance();
    TerrainSegment* segment = terrainGenerator->getTerrainSegmentBasedOnX(spaceship->getXPosition());
    
    if (typeid(LandingPad) != typeid(*segment)) {
        return false;
    } else {
        return landingSucceeds(spaceship, segment);
    }
}


bool CollisionDetector::collisionHappens(Spaceship* spaceship, TerrainSegment* segment) {
    if (segment == NULL) {
        return false;
    }
    
    XInfo* xInfo = XInfo::instance(0, NULL);
    int pixmapHeight = xInfo->getPixmapHeight();
    int shipWidth = spaceship->getWidth();
    int shipHeight = spaceship->getHeight();
    int shipX1 = spaceship->getXPosition();
    int shipY1 = pixmapHeight - spaceship->getYPosition() - shipHeight;
    int shipX2 = shipX1 + shipWidth;
    //int shipY2 = shipY1;
    
    vector<TerrainPoint> boundaryPoints = segment->getBoundaryPoints(shipX1);
    TerrainPoint p1 = boundaryPoints.at(0);
    TerrainPoint p2 = boundaryPoints.at(1);
    
    int p1x = p1.getXCoordinate();
    int p1y = pixmapHeight - p1.getYCoordinate();
    int p2x = p2.getXCoordinate();
    int p2y = pixmapHeight - p2.getYCoordinate();
    
    if (shipY1 > p1y && shipY1 > p2y) {
        return false;
    }
    
    double slope = (p2y - p1y) / (p2x - p1x);
    if (slope * (shipX1 - p1.getXCoordinate()) + p1.getYCoordinate() > 0) {
        return true;
    } else if (slope * (shipX2 - p1.getXCoordinate()) + p1.getYCoordinate() > 0) {
        return true;
    } else {
        return false;
    }
    
}

bool CollisionDetector::landingSucceeds(Spaceship* spaceship, TerrainSegment* segment) {
    double shipYSpeed = spaceship->getYSpeed();
    bool landingHappens = collisionHappens(spaceship, segment);
    bool landingSuccess = landingHappens && (shipYSpeed < landingSpeedLimit);
    return landingSuccess;
}


CollisionDetector::~CollisionDetector() {
    
}



