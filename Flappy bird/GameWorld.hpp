//
//  GameWorld.hpp
//  Flapi Pig
//
//  Created by Ruben on 13/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#ifndef GameWorld_hpp
#define GameWorld_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "PipeColumn.hpp"
#include "Bird.hpp"
#include "Pipe.hpp"
#include "Receiver.hpp"
#include "GInputManager.hpp"

using namespace std;

class GameWorld : public Receiver {
    
private:
    Bird* bird;
    vector<PipeColumn*> cPipes;
    
    GInputManager* gim;
    queue<int> messages;
    
    bool levelFinished;
    float lastPipeColumnX;
    
    
    void handleInput(int msg);
public:
    GameWorld();
    ~GameWorld();
    
    bool isLevelFinished();
    void setLevelFinished(bool finished);
    void initLevel();
    void resetLevel();
    
    void render();
    void logic();
    void pollUpdates();
    void update(float dt);
    
    void checkEndConditions();
    void processMessages();
    void updateCPipes();
};
#endif /* GameWorld_hpp */
