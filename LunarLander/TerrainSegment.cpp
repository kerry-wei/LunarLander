//
//  TerrainSegment.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-21.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "TerrainSegment.h"
#include <stdlib.h>
#include <algorithm>

using namespace std;

TerrainSegment::TerrainSegment(TerrainPoint p1, TerrainPoint p2, PathSpec pathSpec, int numOfPoints) :
    DrawableObject(p1.getXCoordinate(), p1.getYCoordinate(), abs(p2.getXCoordinate() - p1.getXCoordinate()), abs(p2.getYCoordinate() - p1.getYCoordinate())) {
    this->pathSpec = pathSpec;
    this->xInfo = XInfo::instance(0, NULL);
    
    this->generateSegment(p1, p2, pathSpec, numOfPoints);
    this->updateXOffsets();
}

bool TerrainSegment::isOffScreen() {
    TerrainPoint p1 = segmentPath.at(0);
    TerrainPoint p2 = segmentPath.at(segmentPath.size() - 1);
    if (p1.getXCoordinate() > xInfo->getWindowWidth()) {
        return true;
    } else if (p2.getXCoordinate() < 0) {
        return true;
    } else {
        return false;
    }
}

bool TerrainSegment::isCompletelyInsideScreen() {
    int p1X = segmentPath.at(0).getXCoordinate();
    int p2X = segmentPath.at(segmentPath.size() - 1).getXCoordinate();
    if (p1X > 0 && p1X < xInfo->getWindowWidth() && p2X >0 && p2X < xInfo->getWindowWidth()) {
        return true;
    } else {
        return false;
    }
}

void TerrainSegment::shiftTerrainSegment(double deltaX) {
    for (int i = 0; i < segmentPath.size(); i++) {
        TerrainPoint& point = segmentPath.at(i);
        int xCoordinate = point.getXCoordinate();
        point.setXCoordinate(xCoordinate - deltaX);
    }
    updateSegmentPosition();
}

void TerrainSegment::updateRightmostPosition(TerrainPoint point) {
    TerrainPoint &rightmostPoint = segmentPath.at(segmentPath.size() - 1);
    rightmostPoint.setXCoordinate(point.getXCoordinate());
    //rightmostPoint.setYCoordinate(point.getYCoordinate());
    
    // update x-coordinate of the rest of points
    for (int i = (segmentPath.size() - 2 > 0 ? (int)segmentPath.size() - 2 : 0); i >= 0; i--) {
        TerrainPoint &currentPoint = segmentPath.at(i);
        TerrainPoint &nextPoint = segmentPath.at(i + 1);
        currentPoint.setXCoordinate(nextPoint.getXCoordinate() - nextPoint.getXOffsetToPrevious());
    }
    
    updateSegmentPosition();
}

void TerrainSegment::updateLeftmostPosition(TerrainPoint point) {
    TerrainPoint &leftmostPoint = segmentPath.at(0);
    leftmostPoint.setXCoordinate(point.getXCoordinate());
    //leftmostPoint.setYCoordinate(point.getYCoordinate());
    
    // update x-coordinate of the rest of points
    for (int i = 1; i < segmentPath.size(); i++) {
        TerrainPoint &currentPoint = segmentPath.at(i);
        TerrainPoint &previousPoint = segmentPath.at(i - 1);
        currentPoint.setXCoordinate(previousPoint.getXCoordinate() + previousPoint.getXOffsetToNext());
    }
    
    updateSegmentPosition();
}

void TerrainSegment::updateSegmentPosition() {
    // update position:
    TerrainPoint p1 = segmentPath.at(0);
    x = p1.getXCoordinate();
    y = p1.getYCoordinate();
}

vector<TerrainPoint> TerrainSegment::getBoundaryPoints(int x) {
    vector<TerrainPoint> ans = vector<TerrainPoint>();
    for (int i = 0; i < segmentPath.size() - 1; i++) {
        TerrainPoint p1 = segmentPath.at(i);
        TerrainPoint p2 = segmentPath.at(i + 1);
        if (x >= p1.getXCoordinate() && x <= p2.getXCoordinate()) {
            ans.push_back(p1);
            ans.push_back(p2);
            return ans;
        }
    }
    return ans;
}

TerrainPoint TerrainSegment::getLeftmostPoint() {
    return segmentPath.at(0);
}

TerrainPoint TerrainSegment::getRightmostPoint() {
    return segmentPath.at(segmentPath.size() - 1);
}

int TerrainSegment::getLeftmostXCoordinate() {
    TerrainPoint p = segmentPath.at(0);
    return p.getXCoordinate();
}

int TerrainSegment::getRightmostXCoordinate() {
    TerrainPoint p = segmentPath.at(segmentPath.size() - 1);
    return p.getXCoordinate();
}

void TerrainSegment::drawSegment() {
    unsigned long foreground = BlackPixel(xInfo->display, xInfo->screen);
	unsigned long background = WhitePixel(xInfo->display, xInfo->screen);
    draw(foreground, background);
}

void TerrainSegment::clearSegment() {
    unsigned long foreground = WhitePixel(xInfo->display, xInfo->screen);
	unsigned long background = WhitePixel(xInfo->display, xInfo->screen);
    draw(foreground, background);
}

void TerrainSegment::draw(unsigned long foreground, unsigned long background) {
    GC gc = XCreateGC(xInfo->display, xInfo->pixmap, 0, 0);
	XSetForeground(xInfo->display, gc, foreground);
	XSetBackground(xInfo->display, gc, background);
	XSetFillStyle(xInfo->display, gc, FillSolid);
	XSetLineAttributes(xInfo->display, gc, 2, LineSolid, CapRound, JoinMiter);
    XPoint points[segmentPath.size()];
    for (int i = 0; i < segmentPath.size(); i++) {
        TerrainPoint point = segmentPath.at(i);
        points[i].x = point.getXCoordinate();
        points[i].y = point.getYCoordinate();
    }
    XDrawLines(xInfo->display, xInfo->pixmap, gc, points, (int)segmentPath.size(), CoordModeOrigin);
    
    // draw landing pads:
    /*
    vector<LandingPad*>* landingPads = terrain->landingPads;
    for (int i = 0; i < landingPads->size(); i++) {
        LandingPad* landingPad = landingPads->at(i);
        landingPad->draw();
    }
     */
}

void TerrainSegment::printSegment() {
    for (int i = 0; i < segmentPath.size(); i++) {
        TerrainPoint point = segmentPath.at(i);
        cout << "(" << point.getXCoordinate() << ", " << point.getYCoordinate() << ")"
        << ", xOffsetToPrevious = " << point.getXOffsetToPrevious() << ", xOffsetToNext = " << point.getXOffsetToNext() << endl;
        
    }
    cout << "----- segment -----" << endl;
}

void TerrainSegment::generateSegment(TerrainPoint startPoint, TerrainPoint endPoint, PathSpec spec, int numOfPoints) {
    segmentPath = vector<TerrainPoint>(numOfPoints);
    
    if (numOfPoints > 2) {
        bool isUpwardPath = (spec.slope == Up);
        
        int xCoordinates[numOfPoints];
        int yCoordinates[numOfPoints];
        for (int i = 0; i < numOfPoints; i++) {
            xCoordinates[i] = startPoint.getXCoordinate() + rand() % (endPoint.getXCoordinate() - startPoint.getXCoordinate());
        }
        for (int i = 0; i < numOfPoints; i++) {
            int randomDiff = rand() % (startPoint.getYCoordinate() == endPoint.getYCoordinate() ? 50 : abs(startPoint.getYCoordinate() - endPoint.getYCoordinate()));
            short yCoordinate = !isUpwardPath ? (startPoint.getYCoordinate() + randomDiff) : (startPoint.getYCoordinate() - randomDiff);
            
            yCoordinates[i] = yCoordinate;
        }
        
        // sort x-coordiantes:
        sort(xCoordinates, xCoordinates + numOfPoints);
        
        // sort y-coordinates: std::greater<int>()
        if (isUpwardPath) {
            sort(yCoordinates, yCoordinates + numOfPoints, greater<int>());
        } else {
            sort(yCoordinates, yCoordinates + numOfPoints);
        }
        
        for (int i = 1; i < numOfPoints - 1; i++) {
            int xPos = xCoordinates[i];
            int yPos = yCoordinates[i];
            int offsetToPrevious = (i == 0) ? (xPos - startPoint.getXCoordinate()) : (xPos - xCoordinates[i - 1]);
            int offsetToNext = (i == numOfPoints - 1) ? (endPoint.getXCoordinate() - yPos) : (xCoordinates[i + 1] - xPos);
            TerrainPoint point = TerrainPoint(xPos, yPos, offsetToPrevious, offsetToNext);
            segmentPath.at(i) = point;
        }
    }
    
    // add start and end points to vector
    segmentPath.at(0) = startPoint;
    segmentPath.at(numOfPoints - 1) = endPoint;
    
}

void TerrainSegment::updateXOffsets() {
    for (int i = 0; i < segmentPath.size(); i++) {
        TerrainPoint &p = segmentPath.at(i);
        int offsetToPrevious = (i == 0) ? 0 : (abs(p.getXCoordinate() - segmentPath.at(i - 1).getXCoordinate()));
        int offSetToNext = (i == segmentPath.size() - 1) ? 0 : (abs(p.getXCoordinate() - segmentPath.at(i + 1).getXCoordinate()));
        p.setXOffsetToPrevious(offsetToPrevious);
        p.setXOffsetToNext(offSetToNext);
    }
}


TerrainSegment::~TerrainSegment() {
    
}




