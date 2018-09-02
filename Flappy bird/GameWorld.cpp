#include "GameWorld.hpp"
#include "Pipe.hpp"
#include <stdlib.h>

#define K_PIPES_COLUMNS_NUMBER 100
#define K_PIPES_OFFSET 250
#define SCREEN_TOUCH 0

using namespace std;

GameWorld::GameWorld() :
    mBird(GBox(SCREEN_CENTER, kmSizeMake(30, 30), CIRCULAR_SHAPE)),
    mGim(GInputManager()),
    mLevelFinished(false),
    mLastPipeColumnX(-1),
    mMessages()
{
    mBird.GetBox().EnableGravity();
    
    // Add column pipes
    const float MIN_RAND = SCREEN_HEIGHT/6.0, MAX_RAND = SCREEN_HEIGHT - MIN_RAND;
    const float range = MAX_RAND - MIN_RAND;
    for(size_t i = 0; i != K_PIPES_COLUMNS_NUMBER; ++i) {
        float random = range * ((((float) rand()) / (float) RAND_MAX)) + MIN_RAND ;
        float uPipeHeight = random;
        float dPipeHeight = SCREEN_HEIGHT - uPipeHeight - K_COLUMN_PIPES_SPACE;
        
        GBox upPipeBox(kmVec3Make(0, uPipeHeight/2.0, 0.0), kmSizeMake(K_COLUMN_PIPES_WIDTH, uPipeHeight));
        GBox downPipeBox(kmVec3Make(0, SCREEN_HEIGHT - (dPipeHeight/2.0), 0.0), kmSizeMake(K_COLUMN_PIPES_WIDTH, dPipeHeight));
        upPipeBox.SetVelocity(kmVec3Make(k_COLUMN_SPEED, 0, 0));
        downPipeBox.SetVelocity(kmVec3Make(k_COLUMN_SPEED, 0, 0));
        
        mCPipes.emplace_back(upPipeBox, downPipeBox);
    }
    
    GShader::loadAll();
}


bool GameWorld::IsLevelFinished() {
    return mLevelFinished;
}

void GameWorld::SetLevelFinished(bool aFinished) {
    mLevelFinished = aFinished;
}

void GameWorld::InitLevel()
{
    //Set bird
    mBird.GetBox().SetCenter(SCREEN_CENTER);
    mBird.GetBox().SetVelocity(VELOCITY_IDDLE);

    for(int i = 0; i < K_PIPES_COLUMNS_NUMBER; ++i) {
        GLfloat pipeX = SCREEN_WIDTH * 1.5 + (K_PIPES_OFFSET*i);
        mCPipes[i].MoveBy(pipeX);
    }
}

void GameWorld::ResetLevel()
{
    ClearInputMessages();
    GShader::BIRD->disable();
    InitLevel();
}

void GameWorld::ClearInputMessages()
{
    queue<int> qEmpty;
    swap(mMessages, qEmpty);
}

void GameWorld::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 104.0/255.0, 55.0/255.0, 1.0);
    
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    mBird.Render();
    for_each(mCPipes.begin(), mCPipes.end(), [] (PipeColumn& pc){
        pc.Render();
    });
}

void GameWorld::Logic()
{
    UpdateCPipes();
    ProcessMessages();
    CheckEndConditions();
}

void GameWorld::UpdateCPipes()
{
    for(int i = 0; i < mCPipes.size(); ++i) {
        PipeColumn& pc = mCPipes[i];
        if(pc.OutsideLeftLimits()) {
            if(mLastPipeColumnX == -1)
            {
                mLastPipeColumnX = mCPipes[mCPipes.size()-1].GetUp().GetBox().GetCenter().x;
            }
            float offset = 0;
            offset = mLastPipeColumnX + K_PIPES_OFFSET;
            
            Pipe& up = pc.GetUp();
            kmVec3 next = up.GetBox().GetCenter();
            
            pc.MoveTo(next.x + offset);
            mLastPipeColumnX = next.x + offset;
        }
    }
}

void GameWorld::ProcessMessages()
{
    for(int i = 0; i < mMessages.size(); ++i) {
        int messageId = mMessages.front();
        mMessages.pop();
        switch (messageId) {
            case SCREEN_TOUCH:
                mBird.Jump();
                break;
            default:
                break;
        }
    }

}

void GameWorld::CheckEndConditions()
{
    mLevelFinished = (mBird.ReachFloor() || mBird.ReachTop());
    if(!mLevelFinished) {
        for_each(mCPipes.begin(), mCPipes.end(), [this](PipeColumn& pc)
        {
            if(pc.Intersect(mBird)){
                mLevelFinished = true;
            }
        });
    }
}

void GameWorld::Update(double dt)
{
    mBird.Update(dt);
    for_each(mCPipes.begin(), mCPipes.end(), [dt](PipeColumn& pc)
    {
        pc.Update(dt);
    });
}

void GameWorld::PollUpdates() {
    int msgNumber = mGim.getInputsNumber();
    if(msgNumber > 0) {
        for(size_t i = 0; i < msgNumber; ++i) {
            mMessages.push(mGim.remove());
        }
    }
}

void GameWorld::HandleInput(int aMsg)
{
    mGim.addInput(aMsg);
}
