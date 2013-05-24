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
    this->gameState = GameState::instance();
    this->gameObjManager = GameObjectManager::instance();
    this->terrainManager = TerrainManager::instance();
}

void EventLoopManager::startGameLoop() {
    const int BufferSize = 10;
    char text[BufferSize];
    unsigned long lastRepaint = 0;
    
    XWindowAttributes windowAttr;
    XGetWindowAttributes(xInfo->display, xInfo->window, &windowAttr);
    
    GameSceneManager *gameSceneManager = GameSceneManager::instance();
    GameObjectManager *gameObjManager = GameObjectManager::instance();
    Spaceship *spaceship = gameObjManager->getSpaceship();
    TerrainManager *terrainManager = TerrainManager::instance();
    GameState *gameState = GameState::instance();
    CollisionDetector* collisionDetector = CollisionDetector::instance();
    
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
                            if (gameState->isGameStarted()) {
                                spaceship->setYSpeed(-0.05);
                            }
                            
                            break;
                        case XK_Down:
                            if (gameState->isGameStarted()) {
                                spaceship->setYSpeed(0.05);
                            }
                            
                            break;
                        case XK_Left:
                            if (gameState->isGameStarted()) {
                                spaceship->setXSpeed(-0.5); // -0.05
                            }
                            
                            break;
                        case XK_Right:
                            if (gameState->isGameStarted()) {
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
        if (gameState->isGameStarted()) {
            bool crashWillHappen = collisionDetector->spaceshipCrashWillHappen();
            bool landingWillSucceed = collisionDetector->isLandingSuccessful();
            if (crashWillHappen) {
                handleSpaceshipCrash();
            } else if (landingWillSucceed) {
                handleLandingSucceed();
            }
        }
        
        
        if (gameState->isGameStarted()) {
            unsigned long end = Utilities::now();
            if (end - lastRepaint > 1000000 / FPS) {
                int spaceshipX = spaceship->getXPosition();
                int spaceshipY = spaceship->getYPosition();
                double deltaX = spaceship->getXSpeed();
                double deltaY = spaceship->getYSpeed();
                
                if (terrainManager->shouldUpdateTerrain(spaceshipX + deltaX, spaceshipY + deltaY)) {
                    terrainManager->updateTerrainBasedOnSpaceshipPosition(spaceship, deltaX, deltaY);
                    spaceship->playAnimation();
                }
                
                gameObjManager->timerUpdate();
                
                // update game info:
                gameSceneManager->updateGameInfo(0, 0.0, 0.0, (double)(windowAttr.height - spaceship->getYPosition()),
                                                 spaceship->getXSpeed(), spaceship->getYSpeed());
                
                XCopyArea(xInfo->display, xInfo->pixmap, xInfo->window, xInfo->gc[0],
                          0, 0, xInfo->getPixmapWidth(), xInfo->getPixmapHeight(),  // region of pixmap to copy
                          xInfo->pixmapXOffset, xInfo->pixmapYOffset); // position to put top left corner of pixmap in window
                
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
    gameSceneManager->clearScreen();
    gameObjManager->resetSpaceship();
    Spaceship *spaceship = gameObjManager->getSpaceship();
    spaceship->draw();
    
    
    
    XWindowAttributes windowAttr;
    XGetWindowAttributes(xInfo->display, xInfo->window, &windowAttr);
    if (!gameState->isGameStarted() && xInfo->windowSizeIsEnough()) {
        gameState->startGame();
        gameSceneManager->removeWelcomeScreen();
        
        GameObjectManager *gameObjManager = GameObjectManager::instance();
        Spaceship *spaceship = gameObjManager->getSpaceship();
        spaceship->moveToInitialPosition();
        
        terrainManager->initTerrain();
    }
}

void EventLoopManager::handleSpaceshipCrash() {
    cout << "handleSpaceshipCrash: spaceship crashes!" << endl;
    gameState->pauGame();
    gameSceneManager->showSpaceshipCrashScreen();
}

void EventLoopManager::handleLandingSucceed() {
    cout << "handleLandingSucceed: spaceship is landing!" << endl;
    gameState->pauGame();
    gameSceneManager->showLandingSucceedScreen();
}

void EventLoopManager::handleResize(XInfo* xInfo, XEvent &event) {
	XConfigureEvent xce = event.xconfigure;
	fprintf(stderr, "Handling resize  w=%d  h=%d\n", xce.width, xce.height);
    GameSceneManager *gameSceneManager = GameSceneManager::instance();
	if (xce.width > xInfo->getPixmapWidth() && xce.height > xInfo->getPixmapHeight()) {
        repositionPixmap(xce);
	} else if (xce.width < xInfo->getPixmapWidth() || xce.height < xInfo->getPixmapHeight()) {
        // show 'Too Small' message:
        gameSceneManager->showWindowTooSmallMessage();
    }
}

void EventLoopManager::repositionPixmap(XConfigureEvent xce) {
    XClearWindow(xInfo->display, xInfo->window);
    
    // draw boundary
    XDrawRectangle(xInfo->display, xInfo->pixmap, xInfo->gc[0], 0, 0, xInfo->getPixmapWidth(), xInfo->getPixmapHeight());
    
    // re-position pixmap:
    xInfo->pixmapXOffset = (xce.width - xInfo->getPixmapWidth()) / 2;
    xInfo->pixmapYOffset = (xce.height - xInfo->getPixmapHeight()) / 2;
    
    XCopyArea(xInfo->display, xInfo->pixmap, xInfo->window, xInfo->gc[0],
              0, 0, xInfo->getPixmapWidth(), xInfo->getPixmapHeight(),  // region of pixmap to copy
              xInfo->pixmapXOffset, xInfo->pixmapYOffset); // position to put top left corner of pixmap in window
    XFlush(xInfo->display);
}




