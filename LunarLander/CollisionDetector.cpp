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
        bool softLanding = spaceship->getYSpeed() > landingSpeedLimit;
        bool withinLandingPad = segment->isSpaceshipWithinSegment(spaceship);
        return softLanding && withinLandingPad;
    } else {
        return collisionHappens(spaceship);
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
        return landingSucceeds(spaceship);
    }
}


bool CollisionDetector::collisionHappens(Spaceship* spaceship) {
    XInfo* xInfo = XInfo::instance(0, NULL);
    int pixmapHeight = xInfo->getPixmapHeight();
    int shipWidth = spaceship->getWidth();
    int shipHeight = spaceship->getHeight();
    int shipX1 = spaceship->getXPosition();
    int shipY1 = pixmapHeight - spaceship->getYPosition() - shipHeight;
    int shipX2 = shipX1 + shipWidth;
    int shipY2 = shipY1;
    
    TerrainGenerator* terrainGenerator = TerrainGenerator::instance();
    TerrainSegment* segment1 = terrainGenerator->getTerrainSegmentBasedOnX(shipX1);
    TerrainSegment* segment2 = terrainGenerator->getTerrainSegmentBasedOnX(shipX2);
    
    if (segment1 == NULL || segment2 == NULL) {
        return false;
    }
    
    // check left point:
    vector<TerrainPoint> boundaryPoints = segment1->getBoundaryPoints(shipX1);
    TerrainPoint p1 = boundaryPoints.at(0);
    TerrainPoint p2 = boundaryPoints.at(1);
    
    int p1x = p1.getXCoordinate();
    int p1y = pixmapHeight - p1.getYCoordinate();
    int p2x = p2.getXCoordinate();
    int p2y = pixmapHeight - p2.getYCoordinate();
    
    double slope = ((double)(p2y - p1y)) / (double)(p2x - p1x);
    double b = ((double)(p2x * p1y - p2y * p1x)) / (double)(p2x - p1x);
    
    if (slope * shipX1 + b > shipY1) {
        return true;
    }
    
    // check right point:
    boundaryPoints = segment2->getBoundaryPoints(shipX2);
    p1 = boundaryPoints.at(0);
    p2 = boundaryPoints.at(1);
    
    p1x = p1.getXCoordinate();
    p1y = pixmapHeight - p1.getYCoordinate();
    p2x = p2.getXCoordinate();
    p2y = pixmapHeight - p2.getYCoordinate();
    
    slope = ((double)(p2y - p1y)) / (double)(p2x - p1x);
    b = ((double)(p2x * p1y - p2y * p1x)) / (double)(p2x - p1x);
    
    if (slope * shipX2 + b > shipY2) {
        return true;
    }
    
    return false;
}

bool CollisionDetector::landingSucceeds(Spaceship* spaceship) {
    double shipYSpeed = spaceship->getYSpeed();
    bool landingHappens = collisionHappens(spaceship);
    bool landingSuccess = landingHappens && (shipYSpeed < landingSpeedLimit);
    return landingSuccess;
}


CollisionDetector::~CollisionDetector() {
    
}



