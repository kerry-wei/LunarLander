//
//  TerrainGenerator.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-14.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "TerrainGenerator.h"
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include "Utilities.h"
#include "LandingPad.h"

using namespace std;


TerrainGenerator* TerrainGenerator::terrainGenerator = NULL;

TerrainGenerator* TerrainGenerator::instance() {
    if (!terrainGenerator) {
        terrainGenerator = new TerrainGenerator();
    }
    
    return terrainGenerator;
}

TerrainGenerator::TerrainGenerator() {
    xInfo = XInfo::instance(0, NULL);
    int windowWidth = xInfo->getWindowWidth();
    int windowHeight = xInfo->getWindowHeight();
    
    this->activeTerrain = new vector<TerrainSegment*>();
    this->leftInactiveTerrain = new vector<TerrainSegment*>();
    this->rightInactiveTerrain = new vector<TerrainSegment*>();
    
    this->minFlyingSpace = 300;
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    
    srand((unsigned int)time(NULL));
    this->baseNumOfPath = 6;
    this->maxNumOfPath = 12;
    this->numOfTerrainSegment = this->baseNumOfPath + (rand() % (int)(this->maxNumOfPath - this->baseNumOfPath + 1));
    
    this->baseLandingPadCount = 2;
    this->maxLandingPadCount = 4;
    this->landingPadCount = this->baseLandingPadCount
        + (rand() % (int)(this->maxLandingPadCount - this->baseLandingPadCount + 1));
    
    
}

void TerrainGenerator::shiftTerrain(vector<TerrainSegment*>* terrain, double deltaX) {
    for (int i = 0; i < terrain->size(); i++) {
        TerrainSegment* segment = terrain->at(i);
        segment->shiftTerrainSegment(deltaX);
    }
}

void TerrainGenerator::resetAllTerrain() {
    resetTerrain(activeTerrain);
    resetTerrain(leftInactiveTerrain);
    resetTerrain(rightInactiveTerrain);
}

vector<TerrainSegment*>* TerrainGenerator::createInitialTerrain() {
    addTerrainSegments(activeTerrain);
    return activeTerrain;
}

vector<PathSpec> TerrainGenerator::generatePathSpecs(int numOfPathSpec) {
    int numberOfLandingPads = 2;
    vector<PathSpec> pathSpecs = vector<PathSpec>();
    for (int i = 0; i < numOfPathSpec; i++) {
        int randomSlope = rand() % 3;
        if (randomSlope == Horizontal) {
            if (numberOfLandingPads <= 0) {
                randomSlope = (rand() % 1 == 0 ? Down : Up);
            } else {
                numberOfLandingPads -= 1;
            }
        }
        
        PathSpec pathSpec = PathSpec((PathSlope)randomSlope, NormalPath);
        pathSpecs.push_back(pathSpec);
    }
    return pathSpecs;
}

void TerrainGenerator::resetTerrain(vector<TerrainSegment*>* terrain) {
    for (int i = 0; i < terrain->size(); i++) {
        delete terrain->at(i);
    }
    terrain->clear();
}

void TerrainGenerator::addTerrainSegments(vector<TerrainSegment*>* terrain) {
    // generate path specifications:
    vector<PathSpec> pathSpecs = generatePathSpecs(numOfTerrainSegment);
    
    
    const int avgPathLength = windowWidth / numOfTerrainSegment;
    
    const int avgPathUpperLimit = avgPathLength + 10;
    const int avgPathLowerLimit = avgPathLength - 10;
    const int longPathLowerLimit = avgPathLength + 30;
    const int longPathUpperLimit = avgPathLength + 50;
    const int shortPathUpperLimit = avgPathLength - 30;
    const int shortPathLowerLimit = avgPathLength - 50;
    
    const int flatPathUpperLimit = 1;
    const int upPathUpperLimit = 400;
    const int upPathLowerLimit = 200;
    
    // int numOfControlPoints = numOfTerrainSegment + 1;
    vector<TerrainPoint> controlPoints =  vector<TerrainPoint>();//[numOfControlPoints];
    
    // generate control points:
    for (int i = 0; i < numOfTerrainSegment; i++) {
        PathSpec pathSpec = pathSpecs.at(i);
        int pathXComponent, pathYComponent;
        switch (pathSpec.slope) {
            case Up:
                pathYComponent = 0 - upPathLowerLimit + rand() % (upPathUpperLimit - upPathLowerLimit);
                break;
            case Horizontal:
            {
                int upwardFlat = rand() % 2;
                int randomDeltaY = rand() % flatPathUpperLimit;
                pathYComponent = (upwardFlat == 0) ? (0 - randomDeltaY) : randomDeltaY;
            }
                break;
            case Down:
                pathYComponent = upPathLowerLimit + rand() % (upPathUpperLimit - upPathLowerLimit);
                break;
            default:
                string message = "Error: undefined path slope";
                Utilities::reportError(message);
                break;
        }
        
        switch (pathSpec.length) {
            case LongPath:
                pathXComponent = longPathLowerLimit + rand() % (longPathUpperLimit - longPathLowerLimit);
                break;
            case NormalPath:
                pathXComponent = avgPathLowerLimit + rand() % (avgPathUpperLimit - avgPathLowerLimit);
                break;
            case ShortPath:
                pathXComponent = shortPathLowerLimit + rand() % (shortPathUpperLimit - shortPathLowerLimit);
                break;
            default:
                cout << "";
                break;
        }
        
        //cout << "pathXComponent = " << pathXComponent << endl;
        //cout << "pathYComponent = " << pathYComponent << endl;
        
        short endX, endY;
        short previousX = i == 0 ? 0 : controlPoints[i].getXCoordinate();
        short previousY = i == 0 ? (short)(minFlyingSpace + rand() % (windowHeight - minFlyingSpace)) : controlPoints[i].getYCoordinate();
        endY = previousY - pathYComponent;
        // y-coordinate should be bounded: between minFlyingSpace and height of the screen
        if (endY < minFlyingSpace) {
            endY = minFlyingSpace;
        } else if (endY > windowHeight) {
            endY = windowHeight;
        }
        
        if (i == 0) {
            // init first control point:
            TerrainPoint previousControlPoint = TerrainPoint(previousX, previousY);
            controlPoints.push_back(previousControlPoint);
            
            endX = (short)pathXComponent;
        } else if (i == numOfTerrainSegment - 1) {
            endX = (short)windowWidth; // x-coordinate of last control point should always equal width of screen
        } else {
            endX = (short)(previousX + pathXComponent);
        }
        
        // push last control point:
        TerrainPoint controlPoint = TerrainPoint(endX, endY);
        controlPoints.push_back(controlPoint);
    }
    
    // generate path segments:
    for (int i = 0; i < numOfTerrainSegment; i++) {
        TerrainPoint startPoint = controlPoints[i];
        TerrainPoint endPoint = controlPoints[i + 1];
        PathSpec spec = pathSpecs.at(i);
        
        if (spec.slope == Horizontal) {
            // create LandingPad obj
            LandingPad* landingPad = new LandingPad(startPoint, endPoint, spec);
            terrain->push_back(landingPad);
        } else {
            // create TerrainSegment obj
            TerrainSegment* subPath = new TerrainSegment(startPoint, endPoint, spec, 12);
            terrain->push_back(subPath);
        }
        
    }
    
}

bool TerrainGenerator::canShiftTerrainToRight() {
    bool canShiftToRight = leftInactiveTerrain && !leftInactiveTerrain->empty();
    return canShiftToRight;
}

bool TerrainGenerator::shouldCreateLeftTerrain() {
    if (!leftInactiveTerrain) return false;
    return leftInactiveTerrain->empty();
}

bool TerrainGenerator::shouldCreateRightTerrain() {
    if (!rightInactiveTerrain) return false;
    return rightInactiveTerrain->empty();
}

TerrainSegment* TerrainGenerator::getTerrainSegmentBasedOnX(int xPos) {
    for (int i = 0; i < activeTerrain->size(); i++) {
        TerrainSegment* segment = activeTerrain->at(i);
        int leftmostX = segment->getLeftmostXCoordinate();
        int rightmostX = segment->getRightmostXCoordinate();
        if (xPos >= leftmostX && xPos <= rightmostX) {
            return segment;
        }
    }
    return NULL;
}

vector<TerrainSegment*>* TerrainGenerator::getActiveTerrain() {
    return activeTerrain;
}

vector<TerrainSegment*>* TerrainGenerator::getRightShiftedTerrain(double deltaX) {
    shiftTerrain(activeTerrain, deltaX);
    
    // if second last segment is off-screen, move it to rightInactiveTerrain
    TerrainSegment* lastSegment = activeTerrain->at(activeTerrain->size() - 1);
    if (lastSegment->isOffScreen()) {
        rightInactiveTerrain->insert(rightInactiveTerrain->begin(), lastSegment);
        activeTerrain->erase(activeTerrain->end() - 1);
    }
    
    // insert new point to the beginning, if necessary
    TerrainSegment* firstSegment = activeTerrain->at(0);
    if (firstSegment->isCompletelyInsideScreen()) {
        if (!leftInactiveTerrain || leftInactiveTerrain->empty()) {
            Utilities::reportError("ERROR: left inactive terrian should NOT be NULL or empty");
            return NULL;
        }
        
        // pop last element of left inactive terrain, and push it to the beginning of current terrain
        TerrainSegment* lastLeftInactiveSegment = leftInactiveTerrain->at(leftInactiveTerrain->size() - 1);
        lastLeftInactiveSegment->updateRightmostPosition(firstSegment->getLeftmostPoint());
        activeTerrain->insert(activeTerrain->begin(), lastLeftInactiveSegment);
        leftInactiveTerrain->pop_back();
    }
    
    return activeTerrain;
}

vector<TerrainSegment*>* TerrainGenerator::getLeftShiftedTerrain(double deltaX) {
    shiftTerrain(activeTerrain, deltaX);
    
    // if first segment is off screen, move it to leftInactiveTerrain
    TerrainSegment* firstSegment = activeTerrain->at(0);
    if (firstSegment->isOffScreen()) {
        leftInactiveTerrain->push_back(firstSegment);
        activeTerrain->erase(activeTerrain->begin());
    }
    
    // append new segment to current terrain, if necessary:
    TerrainSegment* lastActiveSegment = activeTerrain->at(activeTerrain->size() - 1);
    if (lastActiveSegment->isCompletelyInsideScreen()) {
        if (!rightInactiveTerrain || rightInactiveTerrain->empty()) {
            addTerrainSegments(rightInactiveTerrain);
        }
        
        // pop first element from right inactive terrain, and push first point back to current terrain
        TerrainSegment* firstRightInactiveSegment = rightInactiveTerrain->at(0);
        firstRightInactiveSegment->updateLeftmostPosition(lastActiveSegment->getRightmostPoint());
        activeTerrain->push_back(firstRightInactiveSegment);
        rightInactiveTerrain->erase(rightInactiveTerrain->begin());
        
    }
    
    return activeTerrain;
}

TerrainGenerator::~TerrainGenerator() {
    resetAllTerrain();
    delete activeTerrain;
    delete leftInactiveTerrain;
    delete rightInactiveTerrain;
}


