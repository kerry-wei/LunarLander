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
#include "GameObjectManager.h"
#include "GameSceneManager.h"
#include "GameState.h"
#include "TerrainGenerator.h"
#include "TerrainRenderer.h"
#include "TerrainManager.h"
#include "Spaceship.h"


EventLoopManager::EventLoopManager() {
    this->FPS = 30;
}

void EventLoopManager::handleQuitGame() {
    XInfo *xInfo = XInfo::instance(0, NULL);
    cout << "Terminated normally." << endl;
    XCloseDisplay(xInfo->display);
}

void EventLoopManager::handleStartGame() {
    GameSceneManager *gameSceneManager = GameSceneManager::instance();
    GameState *gameState = GameState::instance();
    XInfo *xInfo = XInfo::instance(0, NULL);
    XWindowAttributes windowAttr;
    XGetWindowAttributes(xInfo->display, xInfo->window, &windowAttr);
    if (!gameState->isGameStarted()) {
        gameState->setGameStarted(true);
        gameSceneManager->removeWelcomeScreen();
        
        GameObjectManager *gameObjManager = GameObjectManager::instance();
        Spaceship *spaceship = gameObjManager->getSpaceship();
        spaceship->moveToInitialPosition();
        
        TerrainGenerator *terrainGenerator = TerrainGenerator::instance();
        vector<TerrainSegment*> *terrain = terrainGenerator->createInitialTerrain();
        TerrainRenderer *terrainRenderer = TerrainRenderer::instance();
        terrainRenderer->drawTerrain(terrain);
    }
}

void EventLoopManager::handleResize(XInfo* xInfo, XEvent &event) {
	XConfigureEvent xce = event.xconfigure;
    GameState *gameState = GameState::instance();
	fprintf(stderr, "Handling resize  w=%d  h=%d\n", xce.width, xce.height);
    
	if (xce.width > xInfo->desiredWidth && xce.height > xInfo->desiredHeight) {
        gameState->setGameStarted(true);
        repositionPixmap(xce);
	} else if (xce.width < xInfo->desiredWidth || xce.height < xInfo->desiredHeight) {
        // flush everything, and show 'Too Small' message:

        gameState->setGameStarted(false);
        
        GameSceneManager *gameSceneManager = GameSceneManager::instance();
        gameSceneManager->showWindowTooSmallMessage();
    }
}

void EventLoopManager::repositionPixmap(XConfigureEvent xce) {
    XInfo *xInfo = XInfo::instance(0, NULL);
    
    // clear pixmap
    XFreePixmap(xInfo->display, xInfo->pixmap);
    int depth = DefaultDepth(xInfo->display, DefaultScreen(xInfo->display));
    xInfo->pixmap = XCreatePixmap(xInfo->display, xInfo->window, xInfo->desiredWidth, xInfo->desiredHeight, depth);
    
    // draw boundary
    XDrawRectangle(xInfo->display, xInfo->pixmap, xInfo->gc[0], 0, 0, xInfo->desiredWidth, xInfo->desiredHeight);
    
    // re-position pixmap:
    xInfo->pixmapXOffset = (xce.width - xInfo->desiredWidth) / 2;
    xInfo->pixmapYOffset = (xce.height - xInfo->desiredHeight) / 2;
    
}

void EventLoopManager::eventloop() {
    const int BufferSize = 10;
    char text[BufferSize];
    unsigned long lastRepaint = 0;
    
    XInfo *xInfo = XInfo::instance(0, NULL);
    XWindowAttributes windowAttr;
    XGetWindowAttributes(xInfo->display, xInfo->window, &windowAttr);
    
    GameSceneManager *gameSceneManager = GameSceneManager::instance();
    GameObjectManager *gameObjManager = GameObjectManager::instance();
    Spaceship *spaceship = gameObjManager->getSpaceship();
    TerrainManager *terrainManager = TerrainManager::instance();
    GameState *gameState = GameState::instance();
    
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
                    int i = XLookupString( (XKeyEvent*)&event, text, BufferSize, &key, 0 );
                    //cout << "KeySym " << key << " text='" << text << "'" << endl;
                    if ( i == 1 && text[0] == 'q' ) {
                        this->handleQuitGame();
                        return;
                    }
                    
                    switch (key) {
                        case 65362: // up
                            if (gameState->isGameStarted()) {
                                spaceship->setYSpeed(-0.05);
                            }
                            
                            break;
                        case 65364: // down
                            if (gameState->isGameStarted()) {
                                spaceship->setYSpeed(0.05);
                            }
                            
                            break;
                        case 65361: // left
                            if (gameState->isGameStarted()) {
                                spaceship->setXSpeed(-0.5); // -0.05
                            }
                            
                            break;
                        case 65363: // right
                            if (gameState->isGameStarted()) {
                                spaceship->setXSpeed(0.5); // 0.05
                            }
                            
                            break;
                            
                        case 32: // space
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
                    //cout << "EventLoopManager: default" << endl;
                    break;
            }
        }
        
        if (gameState->isGameStarted()) {
            // animation timing
            unsigned long end = Utilities::now();
            if (end - lastRepaint > 1000000 / FPS) {
                
                
                int spaceshipX = spaceship->getXPosition();
                int spaceshipY = spaceship->getYPosition();
                double deltaX = spaceship->getXSpeed();
                double deltaY = spaceship->getYSpeed();
                
                
                if (terrainManager->shouldUpdateTerrain(spaceshipX + deltaX, spaceshipY + deltaY)) {
                    terrainManager->updateTerrainBasedOnSpaceshipPosition(spaceship, deltaX, deltaY);
                    spaceship->playAnimation();
                } else {
                    gameObjManager->timerUpdate();
                }
                
                // update game info:
                //double nowInSeconds = Utilities::nowInSeconds();
                gameSceneManager->updateGameInfo(0, 0.0, 0.0, (double)(windowAttr.height - spaceship->getYPosition()),
                                                 spaceship->getXSpeed(), spaceship->getYSpeed());
                
                XCopyArea(xInfo->display, xInfo->pixmap, xInfo->window, xInfo->gc[0],
                          0, 0, xInfo->desiredWidth, xInfo->desiredHeight,  // region of pixmap to copy
                          xInfo->pixmapXOffset, xInfo->pixmapYOffset); // position to put top left corner of pixmap in window
                //XFlush(xInfo->display);
                
                lastRepaint = Utilities::now();
            }
            
            
            
            // give the system time to do other things
            if (XPending(xInfo->display) == 0) {
                usleep(1000000 / FPS - ((unsigned int)end - (unsigned int)lastRepaint));
            }
            
        }
        
    }
    
}




