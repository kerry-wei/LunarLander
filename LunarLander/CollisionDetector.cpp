//
//  CollisionDetector.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-21.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "CollisionDetector.h"

CollisionDetector* CollisionDetector::collisionDetector = NULL;

CollisionDetector* CollisionDetector::instance() {
    if (!collisionDetector) {
        collisionDetector = new CollisionDetector();
    }
    
    return collisionDetector;
}

CollisionDetector::CollisionDetector() {
    terrainManager = TerrainManager::instance();
}


bool CollisionDetector::collisionHappens(Spaceship* spaceship) {
    int shipXPos = spaceship->getXPosition();
    int shipYPos = spaceship->getYPosition();
    
    
}

/*
bool CollisionDetector::isLandingSuccessful(Spaceship* spaceship, LandingPad* landingPad) {
    int shipXPos = spaceship->getXPosition();
    int shipYPos = spaceship->getYPosition();
    
    double spaceXSpeed = spaceship->getXSpeed();
    double spaceYSpeed = spaceship->getYSpeed();
    
    
    
    // TODO: speed too high cause crash
}
 */





CollisionDetector::~CollisionDetector() {
    
}



