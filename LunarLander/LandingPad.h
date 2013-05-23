//
//  LandingPad.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-21.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__LandingPad__
#define __LunarLander__LandingPad__

#include <iostream>
#include "TerrainSegment.h"
#include "TerrainPoint.h"
#include "PathDefinition.h"

using namespace std;

class LandingPad : public TerrainSegment {
public:
    LandingPad(TerrainPoint p1, TerrainPoint p2, PathSpec pathSpce);
    ~LandingPad();
    
    void drawSegment();
    void clearSegment();
    
    
    
private:
    /*
    TerrainPoint* p1;
    TerrainPoint* p2;
     */
    
    void drawLandingPad();
};

#endif /* defined(__LunarLander__LandingPad__) */
