//
//  GameObjectManager.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-16.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__GameObjectManager__
#define __LunarLander__GameObjectManager__

#include <iostream>
#include "Spaceship.h"

using namespace std;

class GameObjectManager {
public:
    static void init();
    static GameObjectManager* instance();
    Spaceship* getSpaceship();
    ~GameObjectManager();
    
    void timerUpdate();
    
private:
    static GameObjectManager* gameObjectManager;
    GameObjectManager();
    Spaceship *spaceship;
};

#endif /* defined(__LunarLander__GameObjectManager__) */
