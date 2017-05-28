//
//  PipeColumn.hpp
//  Flappy bird
//
//  Created by Ruben on 27/5/17.
//  Copyright © 2017 Ruben. All rights reserved.
//

#ifndef PipeColumn_hpp
#define PipeColumn_hpp

#include <stdio.h>
#include "Pipe.hpp"

#define K_COLUMN_PIPES_SPACE 150
#define k_COLUMN_SPEED -100
#define K_COLUMN_PIPES_WIDTH 50

class PipeColumn : public GameObject {
private:
    Pipe* up;
    Pipe* down;
public:
    PipeColumn();
    PipeColumn(int xCenter);
    
    bool outsideLeftLimits();
    bool intersect(GameObject* gObject);
    void update(float dt);
    void render();
};
#endif /* PipeColumn_hpp */
