//
//  Utilities.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-11.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "Utilities.h"
#include <sys/time.h>

void Utilities::reportError( string str ) {
    cerr << str << endl;
    exit(0);
}

unsigned long Utilities::now() {
	timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000000 + tv.tv_usec;
}

double Utilities::nowInSeconds() {
    timeval tv;
	gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec / 1000000;
}

// debug helpers
void Utilities::printControlPoints(vector<TerrainPoint> controlPoints, int controlPointCount) {
    cout << "print control points: " << endl;
    for (int i = 0; i < controlPointCount; i++) {
        TerrainPoint point = controlPoints[i];
        cout << "(" << point.getXCoordinate() << ", " << point.getYCoordinate() << ")" << endl;
    }
}

void Utilities::printTerrain(vector<TerrainSegment> *terrain) {
    cout << "printTerrain: " << endl;
    for (int i = 0; i < terrain->size(); i++) {
        TerrainSegment segment = terrain->at(i);
        segment.printSegment();
    }
    cout << endl;
}

