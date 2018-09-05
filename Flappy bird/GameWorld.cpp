#include "GameWorld.hpp"
#include "GShader.hpp"
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
    mBird.GetBox().SetVelocity(VELOCITY_IDDLE);
    
    // Add column pipes
    const double MIN_RAND = SCREEN_HEIGHT/6.0, MAX_RAND = SCREEN_HEIGHT - MIN_RAND;
    const double range = MAX_RAND - MIN_RAND;
    for(size_t i = 0; i != K_PIPES_COLUMNS_NUMBER; ++i) {
        double random = range * ((((double) rand()) / (double) RAND_MAX)) + MIN_RAND ;
        double uPipeHeight = random;
        double dPipeHeight = SCREEN_HEIGHT - uPipeHeight - K_COLUMN_PIPES_SPACE;
        
        GBox upPipeBox(kmVec3Make(0, uPipeHeight/2.0, 0.0), kmSizeMake(K_COLUMN_PIPES_WIDTH, uPipeHeight));
        GBox downPipeBox(kmVec3Make(0, SCREEN_HEIGHT - (dPipeHeight/2.0), 0.0), kmSizeMake(K_COLUMN_PIPES_WIDTH, dPipeHeight));
        
        upPipeBox.SetVelocity(K_COLUMN_SPEED);
        downPipeBox.SetVelocity(K_COLUMN_SPEED);
        
        mCPipes.emplace_back(upPipeBox, downPipeBox);
    }
    
    GShader::LoadAll();
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

    std::vector<PipeColumn>::size_type i = 0;
    for_each(mCPipes.begin(), mCPipes.end(), [&i](PipeColumn& pc)
    {
        GLfloat pipeX = SCREEN_WIDTH * 1.5 + (K_PIPES_OFFSET*i);
        pc.MoveBy(pipeX);
        ++i;
    });
}

void GameWorld::ResetLevel()
{
    ClearInputMessages();
    GShader::BIRD->Disable();
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
    for_each(mCPipes.begin(), mCPipes.end(), [this](PipeColumn& pc)
    {
        if(pc.OutsideLeftLimits()) {
            if(mLastPipeColumnX == -1)
            {
                mLastPipeColumnX = mCPipes[mCPipes.size()-1].GetUp().GetBox().GetCenter().x;
            }
            double offset = 0;
            offset = mLastPipeColumnX + K_PIPES_OFFSET;
            
            Pipe& up = pc.GetUp();
            kmVec3 next = up.GetBox().GetCenter();
            
            pc.MoveTo(next.x + offset);
            mLastPipeColumnX = next.x + offset;
        }
    });
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
    int msgNumber = mGim.GetInputsNumber();
    if(msgNumber > 0) {
        for(size_t i = 0; i < msgNumber; ++i) {
            mMessages.push(mGim.Remove());
        }
    }
}

void GameWorld::HandleInput(int aMsg)
{
    mGim.AddInput(aMsg);
}
