//
//  PathDefinition.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-21.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef LunarLander_PathDefinition_h
#define LunarLander_PathDefinition_h

typedef enum {
    Up = 0,
    Down,
    Horizontal
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

struct PathSpec {
    PathSlope slope;
    PathLength length;
    PathSpec() {this->slope = Horizontal; this->length = NormalPath;};
    PathSpec(PathSlope slope, PathLength length) {this->slope = slope; this->length = length;};
};

#endif
