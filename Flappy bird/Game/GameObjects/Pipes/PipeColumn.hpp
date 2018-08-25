#ifndef PipeColumn_hpp
#define PipeColumn_hpp

#include <stdio.h>
#include "Pipe.hpp"

#define K_COLUMN_PIPES_SPACE 132
#define k_COLUMN_SPEED -100
#define K_COLUMN_PIPES_WIDTH 50

class PipeColumn : public GObject {
private:
    Pipe* up;
    Pipe* down;
public:
    PipeColumn();
    PipeColumn(int xCenter);
    ~PipeColumn();
    
    Pipe* getUpPipe();
    bool outsideLeftLimits();
    bool intersect(GObject* gObject);
    void update(float dt);
    void moveTo(float xPosition);
    void render();
};
#endif /* PipeColumn_hpp */
