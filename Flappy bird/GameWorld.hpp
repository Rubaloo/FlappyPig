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
#include "MessageManager.hpp"

using namespace std;

class GameWorld : public Receiver {
    
private:
    Bird* bird;
    vector<PipeColumn*> cPipes;
    
    GBox playableArea;
    float gravity;
    MessageManager* mm;
    queue<int> messages;
    
    void handleMessage(int msg);
    
public:
    GameWorld(float gravity);
    ~GameWorld();
    
    float lastPipeColumnX;
    bool add(GObject *gObject);
    bool end;
    
    void render();
    void logic();
    void update(float dt);
    void pollUpdates();
    
    void initLevel();
    void resetLevel();
};
#endif /* GameWorld_hpp */
