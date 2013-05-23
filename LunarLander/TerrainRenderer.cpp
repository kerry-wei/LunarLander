//
//  TerrainRenderer.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-17.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "TerrainRenderer.h"
#include <vector>
#include "XInfo.h"
#include "LandingPad.h"

TerrainRenderer* TerrainRenderer::terrainRenderer = NULL;

TerrainRenderer* TerrainRenderer::instance() {
    if (!terrainRenderer) {
        terrainRenderer = new TerrainRenderer();
    }
    
    return terrainRenderer;
}

TerrainRenderer::TerrainRenderer() {
    
}

void TerrainRenderer::drawTerrain(vector<TerrainSegment*>* terrain) {
    for (int i = 0; i < terrain->size(); i++) {
        TerrainSegment* segment = terrain->at(i);
        segment->drawSegment();
    }
}

void TerrainRenderer::clearTerrain(vector<TerrainSegment*>* terrain) {
    for (int i = 0; i < terrain->size(); i++) {
        TerrainSegment* segment = terrain->at(i);
        segment->clearSegment();
    }
}


TerrainRenderer::~TerrainRenderer() {
    
}




