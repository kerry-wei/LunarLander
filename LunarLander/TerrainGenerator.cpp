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

using namespace std;

typedef enum {
    Up = 0,
    LandingPad,
    Down
} PathSlope;

typedef enum {
    LongPath = 0,
    NormalPath,
    ShortPath
} PathLength;

typedef enum {
    Hard = 0,
    Normal,
    Easy
} GameLevel;

typedef struct {
    PathSlope slope;
    PathLength length;
} PathSpec;

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
    
    this->activeTerrain = new vector<TerrainPoint*>();
    this->leftInactiveTerrain = new vector<TerrainPoint*>();
    this->rightInactiveTerrain = new vector<TerrainPoint*>();
    
    this->minFlyingSpace = 300;
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    
    srand((unsigned int)time(NULL));
    this->baseNumOfPath = 5;
    this->maxNumOfPath = 10;
    this->numOfPath = this->baseNumOfPath + (rand() % (int)(this->maxNumOfPath - this->baseNumOfPath + 1));
    
    this->baseLandingPadCount = 2;
    this->maxLandingPadCount = 4;
    this->landingPadCount = this->baseLandingPadCount
        + (rand() % (int)(this->maxLandingPadCount - this->baseLandingPadCount + 1));
    
    
}


// NOTE: xOffsetToPrevious and xOffsetToNext are not complete
vector<TerrainPoint*>* TerrainGenerator::generateSubPath(TerrainPoint startPoint, TerrainPoint endPoint, int numOfPoints) {
    vector<TerrainPoint*>* subPath = new vector<TerrainPoint*>(numOfPoints);
    
    bool isUpwardPath = TerrainPoint::isUpwardPath(startPoint, endPoint);
    
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
    
    // add middle points:
    for (int i = 0; i < numOfPoints; i++) {
        int xPos = xCoordinates[i];
        int yPos = yCoordinates[i];
        int offsetToPrevious = (i == 0) ? (xPos - startPoint.getXCoordinate()) : (xPos - xCoordinates[i - 1]);
        int offsetToNext = (i == numOfPoints - 1) ? (endPoint.getXCoordinate() - yPos) : (xCoordinates[i + 1] - xPos);
        
        TerrainPoint *point = new TerrainPoint(xPos, yPos, offsetToPrevious, offsetToNext);
        
        subPath->at(i) = point;
    }
    
    // copy end point:
    /*
    XPoint *endPointCopy = new XPoint;
    endPointCopy->x = endPoint.x;
    endPointCopy->y = endPoint.y;
    
    subPath->at(numOfPoints + 1) = endPointCopy;
     */
    
    return subPath;
}

void TerrainGenerator::shiftTerrain(vector<TerrainPoint*> *terrain, double deltaX) {
    for (int i = 0; i < terrain->size(); i++) {
        TerrainPoint *point = terrain->at(i);
        int xCoordinate = point->getXCoordinate();
        point->setXCoordinate(xCoordinate - deltaX);
    }
}

vector<TerrainPoint*>* TerrainGenerator::createInitialTerrain() {
    addTerrain(activeTerrain, 0);
    return activeTerrain;
}

void TerrainGenerator::addTerrain(vector<TerrainPoint*> *terrain, int offSetToPreviousForFirstPoint) {
    // generate path specifications:
    PathSpec pathSpecs[this->numOfPath];
    for (int i = 0; i < this->numOfPath; i++) {
        int randomSlope = rand() % 3;
        pathSpecs[i].slope = (PathSlope)randomSlope;
        pathSpecs[i].length = NormalPath;
        
        //cout << "{" << pathSpecs[i].slope << ", " << pathSpecs[i].length << "}" << endl;
    }
    
    
    const int avgPathLength = windowWidth / numOfPath;
    
    const int avgPathUpperLimit = avgPathLength + 10;
    const int avgPathLowerLimit = avgPathLength - 10;
    const int longPathLowerLimit = avgPathLength + 30;
    const int longPathUpperLimit = avgPathLength + 50;
    const int shortPathUpperLimit = avgPathLength - 30;
    const int shortPathLowerLimit = avgPathLength - 50;
    
    const int flatPathUpperLimit = 1;
    const int upPathUpperLimit = 400;
    const int upPathLowerLimit = 200;
    
    int numOfControlPoints = numOfPath + 1;
    vector<TerrainPoint> controlPoints =  vector<TerrainPoint>();//[numOfControlPoints];
    
    // generate control points:
    for (int i = 0; i < numOfPath; i++) {
        PathSpec pathSpec = pathSpecs[i];
        int pathXComponent, pathYComponent;
        switch (pathSpec.slope) {
            case Up:
                pathYComponent = 0 - upPathLowerLimit + rand() % (upPathUpperLimit - upPathLowerLimit);
                break;
            case LandingPad:
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
        } else if (i == numOfPath - 1) {
            endX = (short)windowWidth; // x-coordinate of last control point should always equal width of screen
        } else {
            endX = (short)(previousX + pathXComponent);
        }
        
        TerrainPoint controlPoint = TerrainPoint(endX, endY);
        controlPoints.push_back(controlPoint);
    }
    
    // debug: print control points:
    cout << "print control points:" << endl;
    Utilities::printControlPoints(controlPoints, numOfControlPoints);
    cout << endl << endl;
    // end
    
    // generate sub path:
    for (int i = 0; i < numOfPath; i++) {
        TerrainPoint startPoint = controlPoints[i];
        TerrainPoint endPoint = controlPoints[i + 1];
        
        vector<TerrainPoint*> *subPath = NULL;
        if (endPoint.getYCoordinate() != startPoint.getYCoordinate()) { // this is not a landing pad
            subPath = this->generateSubPath(startPoint, endPoint, 10);
        } /*else {
            cout << "landing point found" << endl;
        }*/
        
        // add first point of each sub path
        TerrainPoint *startPointCopy = new TerrainPoint(startPoint.getXCoordinate(), startPoint.getYCoordinate());
        terrain->push_back(startPointCopy);
        if (subPath) {
            terrain->insert(terrain->end(), subPath->begin(), subPath->end());
        }
    }
    
    // push back last control point:
    TerrainPoint endPoint = controlPoints[numOfControlPoints - 1];
    TerrainPoint *endPointCopy = new TerrainPoint(
        endPoint.getXCoordinate(),
        endPoint.getYCoordinate()
    );
    terrain->push_back(endPointCopy);
    
    // update xOffsetToPrevious and xOffsetToNext:
    for (int i = 0; i < terrain->size(); i++) {
        TerrainPoint *p = terrain->at(i);
        int offsetToPrevious = (i == 0) ? offSetToPreviousForFirstPoint : (abs(p->getXCoordinate() - terrain->at(i - 1)->getXCoordinate()));
        int offSetToNext = (i == terrain->size() - 1) ? 0 : (abs(p->getXCoordinate() - terrain->at(i + 1)->getXCoordinate()));
        p->setXOffsetToPrevious(offsetToPrevious);
        p->setXOffsetToNext(offSetToNext);
    }
    
    
    // debug:
    /*
    cout << "addTerrain:" << endl;
    Utilities::printTerrainPoint(terrain);
    cout << endl << endl;
     */
    // end
    
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

vector<TerrainPoint*>* TerrainGenerator::getActiveTerrain() {
    return activeTerrain;
}

vector<TerrainPoint*>* TerrainGenerator::getRightShiftedTerrain(double deltaX) {
    shiftTerrain(activeTerrain, deltaX);
    
    // if second last point is off-screen, pop the last point to rightInactiveTerrain
    TerrainPoint *secondLastPoint = activeTerrain->at(activeTerrain->size() - 2);
    TerrainPoint *lastPoint = activeTerrain->at(activeTerrain->size() - 1);
    if (secondLastPoint->getXCoordinate() >= xInfo->getWindowWidth()) {
        rightInactiveTerrain->insert(rightInactiveTerrain->begin(), lastPoint);
        activeTerrain->erase(activeTerrain->end() - 1);
    }
    
    // debug: print left inactive terrain:
    /*
    cout << "getRightShiftedTerrain - right inactive terrain:" << endl;
    Utilities::printTerrainPoint(rightInactiveTerrain);
    cout << endl << endl;
     */
    // end
    
    
    // insert new point to the beginning, if necessary
    TerrainPoint *firstActivePoint = activeTerrain->at(0);
    if (firstActivePoint->getXCoordinate() >= 0) {
        if (!leftInactiveTerrain || leftInactiveTerrain->empty()) {
            Utilities::reportError("ERROR: left inactive terrian should NOT be NULL or empty");
            return NULL;
        }
        
        // pop last element of left inactive terrain, and push it to the beginning of current terrain
        TerrainPoint *lastLeftInactivePoint = leftInactiveTerrain->at(leftInactiveTerrain->size() - 1);
        lastLeftInactivePoint->setXCoordinate(
            firstActivePoint->getXCoordinate() - lastLeftInactivePoint->getXOffsetToNext()
        );
        firstActivePoint->setXOffsetToPrevious(lastLeftInactivePoint->getXOffsetToNext());
        activeTerrain->insert(activeTerrain->begin(), lastLeftInactivePoint);
        leftInactiveTerrain->pop_back();
        
    }
    
    // debug: print left inactive terrain:
    /*
    cout << "getRightShiftedTerrain - left inactive terrain:" << endl;
    Utilities::printTerrainPoint(leftInactiveTerrain);
    cout << endl << endl;
     */
    // end
    
    
    // debug: print current active terrain:
    /*
    cout << "getRightShiftedTerrain - current active terrain:" << endl;
    Utilities::printTerrainPoint(activeTerrain);
    cout << endl << endl;
     */
    // end
    
    
    return activeTerrain;
}

vector<TerrainPoint*>* TerrainGenerator::getLeftShiftedTerrain(double deltaX) {
    shiftTerrain(activeTerrain, deltaX);
    
    // if second point if off-screen, pop the first point to leftInactiveTerrain
    TerrainPoint *secondPoint = activeTerrain->at(1);
    TerrainPoint *firstPoint = activeTerrain->at(0);
    if (secondPoint->getXCoordinate() <= 0) {
        activeTerrain->erase(activeTerrain->begin());
        
        // debug: after erase:
        /*
        cout << "getLeftShiftedTerrain, after erasing first point:" << endl;
        Utilities::printTerrainPoint(activeTerrain);
         */
        // end
        
        leftInactiveTerrain->push_back(firstPoint);
    }
    
    
    
    // debug: print left inactive terrain:
    /*
    cout << "getLeftShiftedTerrain - left inactive terrain:" << endl;
    Utilities::printTerrainPoint(leftInactiveTerrain);
    cout << endl << endl;
     */
    // end
    
    
    // append new point to last, if necessary:
    TerrainPoint *lastActivePoint = activeTerrain->at(activeTerrain->size() - 1);
    if (lastActivePoint->getXCoordinate() <= xInfo->getWindowWidth()) {
        if (!rightInactiveTerrain || rightInactiveTerrain->empty()) {
            // create new right terrain
            addTerrain(rightInactiveTerrain, 10);
        }
        
        // pop first element from right inactive terrain, and push first point back to current terrain
        TerrainPoint *firstRightInactivePoint = rightInactiveTerrain->at(0);
        firstRightInactivePoint->setXCoordinate(
            lastActivePoint->getXCoordinate() + firstRightInactivePoint->getXOffsetToPrevious()
        );
        lastActivePoint->setXOffsetToNext(firstRightInactivePoint->getXOffsetToPrevious());
        rightInactiveTerrain->erase(rightInactiveTerrain->begin());
        activeTerrain->push_back(firstRightInactivePoint);
    }
    
    
    // debug: print right inactive terrain:
    /*
    cout << "getLeftShiftedTerrain - right inactive terrain:" << endl;
    Utilities::printTerrainPoint(rightInactiveTerrain);
    cout << endl << endl;
     */
    // end
    
    
    // debug: print current active terrain:
    /*
    cout << "getLeftShiftedTerrain - current active terrain:" << endl;
    Utilities::printTerrainPoint(activeTerrain);
    cout << endl << endl;
     */
    // end
    
    
    return activeTerrain;
}

TerrainGenerator::~TerrainGenerator() {
    
}






