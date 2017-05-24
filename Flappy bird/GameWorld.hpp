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

#include "Renderer.hpp"
#include "Player.hpp"
#include "Receiver.hpp"
#include "MessageManager.hpp"

using namespace std;

class GameWorld : public Receiver {
    
private:
    Player* bird;
    float gravity;
    MessageManager* mm;
    Renderer* painter;
    vector<GameObject*> gObjects;
    queue<int> messages;
    
    void handleMessage(int msg);
    
public:
    GameWorld(float gravity);
    ~GameWorld();
    
    bool add(GameObject *gObject);
    
    
    void render();
    void logic();
    void update(float dt);
    void pollUpdates();
    void initLevel();
};
#endif /* GameWorld_hpp */
