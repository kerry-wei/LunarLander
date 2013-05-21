//
//  CollisionDetector.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-21.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__CollisionDetector__
#define __LunarLander__CollisionDetector__

#include <iostream>
#include "TerrainManager.h"
#include "LandingPad.h"

class CollisionDetector {
public:
    static CollisionDetector* instance();
    CollisionDetector();
    ~CollisionDetector();
    
    bool collisionHappens(Spaceship* spaceship);
    bool isLandingSuccessful(Spaceship* spaceship, LandingPad* landingPad);
    
private:
    static CollisionDetector* collisionDetector;
    TerrainManager* terrainManager;
};

#endif /* defined(__LunarLander__CollisionDetector__) */
