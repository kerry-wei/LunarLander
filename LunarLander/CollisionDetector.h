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
#include "TerrainSegment.h"

class CollisionDetector {
public:
    static CollisionDetector* instance();
    CollisionDetector();
    ~CollisionDetector();
    
    bool spaceshipCrashWillHappen();
    bool isLandingSuccessful(Spaceship* spaceship, TerrainSegment* landingPad);
    
private:
    static CollisionDetector* collisionDetector;
    TerrainManager* terrainManager;
    
    bool collisionHappens(Spaceship* spaceship, TerrainSegment* segment);
};

#endif /* defined(__LunarLander__CollisionDetector__) */
