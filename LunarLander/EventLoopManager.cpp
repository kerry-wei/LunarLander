//
//  EventLoopManager.cpp
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-11.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#include "EventLoopManager.h"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include "XInfo.h"
#include "Utilities.h"
#include "TerrainGenerator.h"
#include "TerrainManager.h"
#include "Spaceship.h"
#include "CollisionDetector.h"

EventLoopManager::EventLoopManager() {
    this->FPS = 30;
    this->xInfo = XInfo::instance(0, NULL);
    this->gameSceneManager = GameSceneManager::instance();
    //this->gameState = GameState::instance();
    this->gameObjManager = GameObjectManager::instance();
    this->terrainManager = TerrainManager::instance();
    this->collisionDetector = CollisionDetector::instance();
    this->gameContext = GameContext::instance();
}

void EventLoopManager::startGameLoop() {
    const int BufferSize = 10;
    char text[BufferSize];
    unsigned long lastRepaint = 0;
    
    XWindowAttributes windowAttr;
    XGetWindowAttributes(xInfo->display, xInfo->window, &windowAttr);
    
    Spaceship *spaceship = gameObjManager->getSpaceship();
    
    XEvent event; // save the event here
    KeySym key;
    XSelectInput(xInfo->display, xInfo->window, PointerMotionMask | KeyPressMask | StructureNotifyMask); // select events
    
    while(true) {  // event loop until 'exit'
        if (XPending(xInfo->display) > 0) {
            XNextEvent(xInfo->display, &event); // wait for next event
            switch(event.type) {
                case Expose:
                    cout << "Expose" << endl;
                    break;
                case ButtonPress:
                    cout << "mouse button clicked" << endl;
                    break;
                case MotionNotify: // mouse movement
                    //cout << event.xmotion.x << "," << event.xmotion.y << endl;
                    break;
                case KeyPress: // any keypress
                {
                    int i = XLookupString((XKeyEvent*)&event, text, BufferSize, &key, 0);
                    //cout << "KeySym " << key << " text='" << text << "'" << endl;
                    if ( i == 1 && text[0] == 'q' ) {
                        this->handleQuitGame();
                        return;
                    }
                    
                    switch (key) {
                        case XK_Up:
                            if (gameContext->isGameStarted()) {
                                spaceship->setYSpeed(-0.05);
                            }
                            
                            break;
                        case XK_Down:
                            if (gameContext->isGameStarted()) {
                                spaceship->setYSpeed(0.05);
                            }
                            
                            break;
                        case XK_Left:
                            if (gameContext->isGameStarted()) {
                                spaceship->setXSpeed(-0.5); // -0.05
                            }
                            
                            break;
                        case XK_Right:
                            if (gameContext->isGameStarted()) {
                                spaceship->setXSpeed(0.5); // 0.05
                            }
                            
                            break;
                            
                        case XK_space:
                            handleStartGame();
                            break;
                        default:
                            break;
                    }
                    break;
                }
                    
                case ConfigureNotify:
					handleResize(xInfo, event);
					break;
                case GenericEvent:
                    cout << "generic event" << endl;
                    break;
                case LASTEvent:
                    cout << "last event" << endl;
                    break;
                default:
                    break;
            }
        }
        
        // check collision:
        if (gameContext->isGameStarted()) {
            bool crashWillHappen = collisionDetector->spaceshipCrashWillHappen();
            bool landingWillSucceed = collisionDetector->isLandingSuccessful();
            if (crashWillHappen) {
                handleSpaceshipCrash();
            } else if (landingWillSucceed) {
                handleLandingSucceed();
            }
        }
        
        
        if (gameContext->isGameStarted()) {
            unsigned long end = Utilities::now();
            if (end - lastRepaint > 1000000 / FPS) {
                int spaceshipX = spaceship->getXPosition();
                int spaceshipY = spaceship->getYPosition();
                double xSpeed = spaceship->getXSpeed();
                double ySpeed = spaceship->getYSpeed();
                
                if (terrainManager->shouldUpdateTerrain(spaceshipX + xSpeed, spaceshipY + ySpeed)) {
                    terrainManager->updateTerrainBasedOnSpaceshipPosition(spaceship, xSpeed, ySpeed);
                }
                
                gameObjManager->timerUpdate();
                
                // update game info:
                gameSceneManager->updateGameInfo(0, 0.0, 0.0, (double)(windowAttr.height - spaceship->getYPosition()), xSpeed, ySpeed);
                
                Display* display = xInfo->display;
                Drawable pixmap = xInfo->pixmap;
                Drawable window = xInfo->window;
                GC gc = xInfo->gc[0];
                int copyWidth = xInfo->getPixmapWidth();
                int copyHeight = xInfo->getPixmapHeight();
                int offsetX = xInfo->pixmapXOffset;
                int offsetY = xInfo->pixmapYOffset;
                XCopyArea(display, pixmap, window, gc, 0, 0, copyWidth, copyHeight, offsetX, offsetY);
                
                lastRepaint = Utilities::now();
            }
            
            // give the system time to do other things
            if (XPending(xInfo->display) == 0) {
                usleep(1000000 / FPS - ((unsigned int)end - (unsigned int)lastRepaint));
            }
        }
    }
}


void EventLoopManager::handleQuitGame() {
    cout << "Terminated normally." << endl;
    XCloseDisplay(xInfo->display);
}

void EventLoopManager::handleStartGame() {
    gameContext->start();
}

void EventLoopManager::handleSpaceshipCrash() {
    cout << "handleSpaceshipCrash: spaceship crashes!" << endl;
    
    gameContext->lose();
}

void EventLoopManager::handleLandingSucceed() {
    cout << "handleLandingSucceed: spaceship is landing!" << endl;
    
    // TODO: fix this, should NOT show crash screen
    gameContext->win();
}

void EventLoopManager::handleResize(XInfo* xInfo, XEvent &event) {
	XConfigureEvent xce = event.xconfigure;
	fprintf(stderr, "Handling resize  w=%d  h=%d\n", xce.width, xce.height);
    
	if (xce.width > xInfo->getPixmapWidth() && xce.height > xInfo->getPixmapHeight()) {
        gameContext->resume(xce);
	} else if (xce.width < xInfo->getPixmapWidth() || xce.height < xInfo->getPixmapHeight()) {
        gameContext->pause();
    }
}


