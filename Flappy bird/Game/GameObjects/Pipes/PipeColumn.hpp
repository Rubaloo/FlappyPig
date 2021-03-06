#ifndef PipeColumn_hpp
#define PipeColumn_hpp

#define K_COLUMN_PIPES_SPACE 132
#define K_COLUMN_SPEED kmVec3Make(-100, 0, 0)
#define K_COLUMN_PIPES_WIDTH 50

#include "Pipe.hpp"

class PipeColumn
{
private:
    Pipe mUp;
    Pipe mDown;
public:
    PipeColumn(const GBox& aUpBox, const GBox& aDownBox);
    
    Pipe& GetUp();
    bool OutsideLeftLimits();
    bool Intersect(GObject& gObject);
    void Update(float dt);
    void MoveTo(float xPosition);
    void MoveBy(float xPosition);
    void Render();
    void FreeModelMesh();
};
#endif /* PipeColumn_hpp */
