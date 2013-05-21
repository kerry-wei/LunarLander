//
//  TerrainPoint.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-18.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "TerrainPoint.h"


TerrainPoint::TerrainPoint() {
    this->xPoint = XPoint();
    this->xOffsetToPrevious = 0;
    this->xOffsetToNext = 0;
}

TerrainPoint::TerrainPoint(int x, int y) {
    this->xPoint = XPoint();
    this->xPoint.x = x;
    this->xPoint.y = y;
}

TerrainPoint::TerrainPoint(int x, int y, int xOffsetToPrevious, int xOffsetToNext) {
    this->xPoint = XPoint();
    this->xPoint.x = x;
    this->xPoint.y = y;
    this->xOffsetToPrevious = xOffsetToPrevious;
    this->xOffsetToNext = xOffsetToNext;
}

TerrainPoint::TerrainPoint(const TerrainPoint &point) {
    this->xPoint.x = point.xPoint.x;
    this->xPoint.y = point.xPoint.y;
    this->xOffsetToPrevious = point.xOffsetToPrevious;
    this->xOffsetToNext = point.xOffsetToNext;
}

XPoint TerrainPoint::getXPoint() {
    return xPoint;
}

void TerrainPoint::setPosition(int x, int y) {
    xPoint.x = x;
    xPoint.y = y;
}

void TerrainPoint::setXCoordinate(int x) {
    xPoint.x = x;
}

void TerrainPoint::setYCoordinate(int y) {
    xPoint.y = y;
}

int TerrainPoint::getXCoordinate() {
    return  xPoint.x;
}

int TerrainPoint::getYCoordinate() {
    return xPoint.y;
}

void TerrainPoint::setXOffsetToPrevious(int offset) {
    xOffsetToPrevious = offset;
}

void TerrainPoint::setXOffsetToNext(int offset) {
    xOffsetToNext = offset;
}

int TerrainPoint::getXOffsetToPrevious() {
    return xOffsetToPrevious;
}

int TerrainPoint::getXOffsetToNext() {
    return xOffsetToNext;
}

bool TerrainPoint::isUpwardPath(TerrainPoint p1, TerrainPoint p2) {
    return p1.xPoint.y < p2.xPoint.y;
}






