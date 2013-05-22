//
//  Utilities.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-11.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__Utilities__
#define __LunarLander__Utilities__

#include <iostream>
#include <cstdlib>
#include <vector>
#include "TerrainPoint.h"
#include "TerrainSegment.h"

using namespace std;

class Utilities {
public:
    static void reportError(string str);
    static unsigned long now();
    static double nowInSeconds();
    static void printControlPoints(vector<TerrainPoint> controlPoints, int controlPointCount);
    static void printTerrain(vector<TerrainSegment> *terrain);
};

#endif /* defined(__LunarLander__Utilities__) */
