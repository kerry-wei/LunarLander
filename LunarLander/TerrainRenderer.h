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
#include <vector>
#include <X11/Xlib.h>
#include "TerrainPoint.h"

using namespace std;

class TerrainRenderer {
public:
    static TerrainRenderer* instance();
    
    TerrainRenderer();
    ~TerrainRenderer();
    
    void drawTerrain(vector<TerrainPoint*>* terrain);
    void clearTerrain(vector<TerrainPoint*>* terrain);
    
private:
    static TerrainRenderer* terrainRenderer;
    void renderTerrain(vector<TerrainPoint*>* terrain, unsigned long foreground, unsigned long background);
    
};

#endif /* defined(__LunarLander__TerrainRenderer__) */
