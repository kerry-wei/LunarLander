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
#include "DrawableObject.h"
#include "TerrainPoint.h"

using namespace std;

class LandingPad : public DrawableObject {
public:
    LandingPad();
    LandingPad(TerrainPoint* p1, TerrainPoint* p2);
    ~LandingPad();
    
    void draw();
    
private:
    TerrainPoint* p1;
    TerrainPoint* p2;
};

#endif /* defined(__LunarLander__LandingPad__) */
