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

class GameWorld : public Receiver
{
public:
    GameWorld();
    ~GameWorld();
    
    bool IsLevelFinished();
    void SetLevelFinished(bool aFinished);
    
    void InitLevel();
    void ResetLevel();
    
    void Render();
    void Logic();
    void PollUpdates();
    void Update(double dt);
    
private:
    Bird mBird;
    GInputManager mGim;
    bool mLevelFinished;
    float mLastPipeColumnX;
    /**
     * Data structure to store user input
     */
    std::queue<int> mMessages;
    std::vector<PipeColumn> mCPipes;
    
    void CheckEndConditions();
    void UpdateCPipes();
    
    void ProcessMessages();
    void ClearInputMessages();
    
    void HandleInput(int aMsg);
    
};
#endif /* GameWorld_hpp */
