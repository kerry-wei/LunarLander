//
//  Spaceship.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-15.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "Spaceship.h"
#include "DrawableObject.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>


Spaceship::Spaceship() : DrawableObject() {
    initialX = 150;
    initialY = 10;
    xSpeed = 0.0;
    ySpeed = 0.0;
    xSpeedLimit = 3.0;
    ySpeedLimit = 3.0;
    
    animationFrameCount = 11;
    animationFrameIndex = 0;
    
}

Spaceship::Spaceship(int x, int y) : DrawableObject(x, y) {
    initialX = 150;
    initialY = 10;
    xSpeed = 1.0;
    ySpeed = 0.0;
    xSpeedLimit = 2.5;
    ySpeedLimit = 4.0;
    
    animationFrameCount = 11;
    animationFrameIndex = 0;
    animations = new vector<Pixmap>(animationFrameCount);
    for (int i = 1; i <= animationFrameCount; i++) {
        int x_hot_return, y_hot_return;
        unsigned int image_width, image_height;
        
        int indexDigit = i / 10 + 1;
        int fileNameSize = 12 + i / 10;
        char fileNamePrefix[] = "frame_";
        char fileNameSuffix[] = ".bmp";
        char fileIndex[3];
        snprintf(fileIndex, indexDigit + 1, "%d", i);
        char fileName[fileNameSize];
        
        strncpy(fileName, fileNamePrefix, sizeof(fileNamePrefix));
        strncat(fileName, fileIndex, indexDigit + 1);
        strncat(fileName, fileNameSuffix, sizeof(fileName) - strlen(fileName) - 1);
        
        int result = XReadBitmapFile(
           xInfo->display,
           xInfo->pixmap,
           fileName,
           &image_width,
           &image_height,
           &animations->at(i - 1),
           &x_hot_return,
           &y_hot_return
        );
        
        switch (result) {
            case BitmapOpenFailed:
                fprintf(stderr, "XReadBitmapFile - could not open file '%s'.\n", fileName);
                exit(1);
                break;
            case BitmapFileInvalid:
                fprintf(stderr,
                        "XReadBitmapFile - file '%s' doesn't contain a valid bitmap.\n",
                        fileName);
                exit(1);
                break;
            case BitmapNoMemory:
                fprintf(stderr, "XReadBitmapFile - not enough memory.\n");
                exit(1);
                break;
            case BitmapSuccess:
                break;
            default:
                cout << "default" << endl;
                break;
        }
        
        this->width = image_width;
        this->height = image_height;
        
        //cout << "width = " << width << ", height = " << height << endl;
        
    }
}

void Spaceship::reset() {
    initialX = 150;
    initialY = 10;
    xSpeed = 0.0;
    ySpeed = 0.0;
    xSpeedLimit = 3.0;
    ySpeedLimit = 3.0;
    
    animationFrameIndex = 0;
}

void Spaceship::move(int deltaX, int deltaY) {
    int windowWidth = xInfo->getWindowWidth();
    
    if (x + deltaX <= 0 || y + deltaY + height <= 0 || x + deltaX + width >= windowWidth) {
        return;
    }
    
    this->clearDrawing();
    DrawableObject::move(deltaX, deltaY);
    
    // cout << "move - spaceship position: (" << x << ", " << y << ")" << endl;
    
    this->draw();
}

void Spaceship::moveToInitialPosition() {
    this->clearDrawing();
    x = initialX;
    y = initialY;
    this->draw();
}

void Spaceship::draw() {
    XInfo *xInfo = XInfo::instance(0, NULL);
    GC gc = xInfo->gc[0];
    XCopyPlane(xInfo->display, animations->at(animationFrameIndex), xInfo->pixmap, gc, 0, 0, width, height, x, y, 1);
}

void Spaceship:: playAnimation() {
    if (animationFrameIndex == 10) {
        animationFrameIndex = 0;
    } else {
        animationFrameIndex += 1;
    }
    
    this->clearDrawing();
    this->draw();
}

void Spaceship::timerUpdate() {
    ySpeed += 0.012;
    
    // cout << "xSpeed = " << xSpeed << ", ySpeed = " << ySpeed << endl;
    
    move(xSpeed, ySpeed);
    playAnimation();
}

void Spaceship::setXSpeed(double delta) {
    xSpeed += delta;
    
    if (abs(xSpeed) > abs(xSpeedLimit)) {
        xSpeed = xSpeed > 0.0 ? xSpeedLimit : (0.0 - xSpeedLimit);
    }
}
void Spaceship::setYSpeed(double delta) {
    //cout << "before: y = " << ySpeed << ", delta = " << delta << endl;
    
    ySpeed += delta;
    
    //cout << "after: y = " << ySpeed << ", delta = " << delta << endl;
    
    if (ySpeed > abs(ySpeedLimit)) {
        ySpeed = ySpeed > 0.0 ? ySpeedLimit : (0.0 - ySpeedLimit);
    }
    
    //cout << "after abs: y = " << ySpeed << ", delta = " << delta << endl;
    
}

bool Spaceship::isMovingLeft() {
    return xSpeed < 0;
}

bool Spaceship::isMovingRight() {
    return xSpeed > 0;
}


double Spaceship::getXSpeed() {
    return xSpeed;
}

double Spaceship::getYSpeed() {
    return ySpeed;
}





