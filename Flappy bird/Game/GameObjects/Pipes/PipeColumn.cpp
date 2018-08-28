#include "PipeColumn.hpp"


PipeColumn::PipeColumn(){}
PipeColumn::PipeColumn(int xCenter) {
    const float MIN_RAND = SCREEN_HEIGHT/6.0, MAX_RAND = SCREEN_HEIGHT - MIN_RAND;
    const float range = MAX_RAND - MIN_RAND;
    float random = range * ((((float) rand()) / (float) RAND_MAX)) + MIN_RAND ;
    
    float uPipeHeight = random;
    float dPipeHeight = SCREEN_HEIGHT - uPipeHeight - K_COLUMN_PIPES_SPACE;
    
    GBox uPipeBox(kmVec3Make(xCenter, uPipeHeight/2.0, 0.0), kmSizeMake(K_COLUMN_PIPES_WIDTH, uPipeHeight));
    GBox dPipeBox(kmVec3Make(xCenter, SCREEN_HEIGHT - (dPipeHeight/2.0), 0.0), kmSizeMake(K_COLUMN_PIPES_WIDTH, dPipeHeight));
    uPipeBox.setVelocity(kmVec3Make(k_COLUMN_SPEED, 0, 0));
    dPipeBox.setVelocity(kmVec3Make(k_COLUMN_SPEED, 0, 0));
    
    up = new Pipe(uPipeBox);
    down = new Pipe(dPipeBox);
}

PipeColumn::~PipeColumn(){
    delete up;
    delete down;
}

bool PipeColumn::intersect(GObject* gObject)
{
    return (up->intersect(gObject)) || (down->intersect(gObject));
}

void PipeColumn::update(float dt)
{
    up->update(dt);
    down->update(dt);
}

Pipe* PipeColumn::getUpPipe()
{
    return up;
}

bool PipeColumn::outsideLeftLimits()
{
    return up->outsideLeftLimits() || down->outsideLeftLimits();
}

void PipeColumn::moveTo(float xTranslation)
{
    up->moveTo(kmVec3Make(xTranslation, 0, 0));
    down->moveTo(kmVec3Make(xTranslation, 0, 0));
}

void PipeColumn::render() {
    up->render();
    down->render();
};

void PipeColumn::freeModelMesh()
{
    up->freeModelMesh();
    down->freeModelMesh();
}
