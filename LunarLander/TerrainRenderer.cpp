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

TerrainRenderer* TerrainRenderer::terrainRenderer = NULL;

TerrainRenderer* TerrainRenderer::instance() {
    if (!terrainRenderer) {
        terrainRenderer = new TerrainRenderer();
    }
    
    return terrainRenderer;
}

TerrainRenderer::TerrainRenderer() {
    
}

void TerrainRenderer::drawTerrain(vector<TerrainSegment>* terrain) {
    XInfo *xInfo = XInfo::instance(0, NULL);
    unsigned long foreground = BlackPixel(xInfo->display, xInfo->screen);
	unsigned long background = WhitePixel(xInfo->display, xInfo->screen);
    renderTerrain(terrain, foreground, background);
}

void TerrainRenderer::clearTerrain(vector<TerrainSegment>* terrain) {
    XInfo *xInfo = XInfo::instance(0, NULL);
    unsigned long foreground = WhitePixel(xInfo->display, xInfo->screen);
	unsigned long background = WhitePixel(xInfo->display, xInfo->screen);
    renderTerrain(terrain, foreground, background);
}

void TerrainRenderer::renderTerrain(vector<TerrainSegment>* terrain, unsigned long foreground, unsigned long background) {
    XInfo *xInfo = XInfo::instance(0, NULL);
    GC gc = XCreateGC(xInfo->display, xInfo->window, 0, 0);
	XSetForeground(xInfo->display, gc, foreground);
	XSetBackground(xInfo->display, gc, background);
	XSetFillStyle(xInfo->display, gc, FillSolid);
	XSetLineAttributes(xInfo->display, gc, 2, LineSolid, CapRound, JoinMiter);
    /*
    XPoint points[terrain->path->size()];
    for (int i = 0; i < terrain->path->size(); i++) {
        TerrainPoint *point = terrain->path->at(i);
        points[i].x = point->getXCoordinate();
        points[i].y = point->getYCoordinate();
    }
    XDrawLines(xInfo->display, xInfo->pixmap, gc, points, (int)terrain->path->size(), CoordModeOrigin);
     */
    for (int i = 0; i < terrain->size(); i++) {
        TerrainSegment segment = terrain->at(i);
        segment.draw(foreground, background);
    }
    
    // draw landing pads:
    /*
    vector<LandingPad*>* landingPads = terrain->landingPads;
    for (int i = 0; i < landingPads->size(); i++) {
        LandingPad* landingPad = landingPads->at(i);
        landingPad->draw();
    }
     */
}

TerrainRenderer::~TerrainRenderer() {
    
}




