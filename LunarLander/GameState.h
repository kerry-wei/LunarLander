//
//  GameState.h
//  LunarLander
//
//  Created by Xiaojiang Wei on 2013-05-16.
//  Copyright (c) 2013 Xiaojiang Wei. All rights reserved.
//

#ifndef __LunarLander__GameState__
#define __LunarLander__GameState__

#include <iostream>



class GameState {
public:
    static GameState* instance();
    static void init();
    GameState();
    ~GameState();
    
    bool isGameStarted();
    void pauGame();
    void startGame();
    
private:
    static GameState *gameState;
    bool gameStarted;
    
    void setGameStarted(bool started);
};

#endif /* defined(__LunarLander__GameState__) */
