#define K_PLAYER_JUMP 24000

#include "Bird.hpp"

Bird::Bird(const GBox& aBody) : GObject(aBody)
{
    kmSize size = aBody.GetSize();
    
    GLfloat w = (size.w*ASPECT_RATIO)/SCREEN_WIDTH;
    GLfloat h = size.h/SCREEN_HEIGHT;

    GLfloat h2 = h/2.0;
    GLfloat w2 = w/2.0;
    
    
    glVertex modelVertexs[] = {
        {{-w2, h2, 0},{1,0,0,1}},
        {{w2, h2, 0},{0,1,0,1}},
        {{-w2, -h2, 0},{0,0,1,1}},
        {{w2,-h2, 0},{1,0,0,1}}
    };
    
    ResetModelView();
    MoveBy(aBody.GetCenter());
    GLubyte modelIndexs[] = {0,1,2,3};
    mMmodelMesh = GVertexArray(modelVertexs, modelIndexs);
}

Bird::~Bird(){
    mMmodelMesh.Unbind();
};

void Bird::Jump() {
    mBody.SetVelocity(kmVec3Make(0, 0, 0));
    mBody.ApplyImpulse(K_PLAYER_JUMP, kmVec3Make(0, -1, 0));
}
void Bird::Update(double dt)
{
    kmVec3 nextPosition = mBody.Update(dt);
    MoveBy(nextPosition);
}

void Bird::Render() {
    
    GLMatrix projection;
    projection.populateOrtho(0, ASPECT_RATIO, 1, 0, -1, 1);
    
    GShader::BIRD->Enable();
    GShader::BIRD->EnableVertexAttribute("Position");
    GShader::BIRD->EnableVertexAttribute("SourceColor");
    
    kmMat4 gMatrix;
    mModelView.gMatrix(&gMatrix);
    GShader::BIRD->SetUniform4f("ModelView", gMatrix.mat);
    GShader::BIRD->SetUniform4f("Projection", projection.matrix());
    
    kmVec3 position = GetBox().GetCenter();
    GShader::BIRD->SetUniform1f("xPosition", position.x);
    GShader::BIRD->SetUniform1f("yPosition", SCREEN_HEIGHT - position.y);
    GShader::BIRD->SetUniform1f("radius", 15.0);
    
    mMmodelMesh.Render();
    ResetModelView();
    GShader::BIRD->Disable();
    

};
