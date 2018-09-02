#include "GameWorld.hpp"
#include "Pipe.hpp"
#include <stdlib.h>

#define K_PIPES_COLUMNS_NUMBER 100
#define K_PIPES_OFFSET 250
#define SCREEN_TOUCH 0

GameWorld::GameWorld() : bird(GBox(SCREEN_CENTER, kmSizeMake(30, 30), CIRCULAR_SHAPE))
{
    bird.getBox()->enableGravity();
    
    for(int i = 0; i < K_PIPES_COLUMNS_NUMBER; ++i) {
        cPipes.emplace_back(0);
    }
    
    levelFinished = false;
    lastPipeColumnX = -1;
    
    GShader::loadAll();
    gim = new GInputManager();
}


bool GameWorld::isLevelFinished() {
    return levelFinished;
}

void GameWorld::setLevelFinished(bool finished) {
    levelFinished = finished;
}

void GameWorld::initLevel()
{
    //Set bird
    bird.getBox()->setCenter(SCREEN_CENTER);
    bird.getBox()->setVelocity(VELOCITY_IDDLE);

    for(int i = 0; i < K_PIPES_COLUMNS_NUMBER; ++i) {
        GLfloat pipeX = SCREEN_WIDTH * 1.5 + (K_PIPES_OFFSET*i);
        cPipes[i].moveBy(pipeX);
    }
    
}

void GameWorld::clearLevelReferences()
{
    queue<int> qEmpty;
    swap(messages, qEmpty);
}

void GameWorld::resetLevel()
{
    clearLevelReferences();
    GShader::BIRD->
    GShader::BIRD->disable();
    initLevel();
}

GameWorld::~GameWorld()
{
    clearLevelReferences();
    delete gim;
}

void GameWorld::render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 104.0/255.0, 55.0/255.0, 1.0);
    
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    bird.render();
    for(int i = 0; i < cPipes.size(); ++i) {
        cPipes[i].render();
    }
}

void GameWorld::logic()
{
    updateCPipes();
    processMessages();
    checkEndConditions();
}

void GameWorld::updateCPipes()
{
    for(int i = 0; i < cPipes.size(); ++i) {
        PipeColumn& pc = cPipes[i];
        if(pc.outsideLeftLimits()) {
            if(lastPipeColumnX == -1) {
                lastPipeColumnX = cPipes[cPipes.size()-1].getUpPipe().getBox()->getCenter().x;
            }
            float offset = 0;
            offset = lastPipeColumnX + K_PIPES_OFFSET;
            
            Pipe& up = pc.getUpPipe();
            kmVec3 next = up.getBox()->getCenter();
            
            pc.moveTo(next.x + offset);
            lastPipeColumnX = next.x + offset;
        }
    }
}

void GameWorld::processMessages()
{
    for(int i = 0; i < messages.size(); ++i) {
        int messageId = messages.front();
        messages.pop();
        switch (messageId) {
            case SCREEN_TOUCH:
                bird.jump();
                break;
            default:
                break;
        }
    }

}

void GameWorld::checkEndConditions()
{
    levelFinished = (bird.reachFloor() || bird.reachTop());
    if(!levelFinished) {
        for(int i = 0; i < cPipes.size(); ++i) {
            PipeColumn& pc = cPipes[i];
            if(pc.intersect(&bird)){
                levelFinished = true;
            }
        }
    }
}

void GameWorld::update(float dt)
{
    bird.update(dt);
    for(int i = 0; i < cPipes.size(); ++i) {
        cPipes[i].update(dt);
    }
}

void GameWorld::pollUpdates() {
    int msgNumber = gim->getInputsNumber();
    if(msgNumber > 0) {
        for(int i = 0; i < msgNumber; ++i) {
            messages.push(gim->remove());
        }
    }
}

void GameWorld::handleInput(int msg)
{
    gim->addInput(msg);
}
