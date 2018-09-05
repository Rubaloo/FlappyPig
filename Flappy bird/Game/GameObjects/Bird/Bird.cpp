#define K_PLAYER_JUMP 24000

#include "Bird.hpp"
#include "GShader.hpp"
#include "GDirector.hpp"

Bird::Bird(const GBox& aBody) : GObject(aBody)
{}

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
    projection.PopulateOrtho(0, ASPECT_RATIO, 1, 0, -1, 1);
    
    GShader::BIRD->Enable();
    GShader::BIRD->EnableVertexAttribute("Position");
    GShader::BIRD->EnableVertexAttribute("SourceColor");
    
    kmMat4 gMatrix;
    mModelView.gMatrix(&gMatrix);
    GShader::BIRD->SetUniform4f("ModelView", gMatrix.mat);
    GShader::BIRD->SetUniform4f("Projection", projection.Matrix());
    
    kmVec3 position = GetBox().GetCenter();
    GShader::BIRD->SetUniform1f("xPosition", position.x);
    GShader::BIRD->SetUniform1f("yPosition", SCREEN_HEIGHT - position.y);
    GShader::BIRD->SetUniform1f("radius", 15.0);
    
    mModelMesh.Render();
    ResetModelView();
    GShader::BIRD->Disable();
    

};
