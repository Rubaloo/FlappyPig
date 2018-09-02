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
    Bird bird;
    GInputManager gim;
    vector<PipeColumn> cPipes;
    
    
    queue<int> messages;
    
    bool levelFinished;
    float lastPipeColumnX;
    
    void checkEndConditions();
    void processMessages();
    void updateCPipes();
    void clearLevelReferences();
    
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
};
#endif /* GameWorld_hpp */
