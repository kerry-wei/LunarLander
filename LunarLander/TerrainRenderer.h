//
//  TerrainRenderer.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-17.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__TerrainRenderer__
#define __LunarLander__TerrainRenderer__

#include <iostream>
#include <X11/Xlib.h>
#include <vector>
#include "TerrainSegment.h"

using namespace std;

class TerrainRenderer {
public:
    static TerrainRenderer* instance();
    
    TerrainRenderer();
    ~TerrainRenderer();
    
    void drawTerrain(vector<TerrainSegment*>* terrain);
    void clearTerrain(vector<TerrainSegment*>* terrain);
    
private:
    static TerrainRenderer* terrainRenderer;
    
};

#endif /* defined(__LunarLander__TerrainRenderer__) */
