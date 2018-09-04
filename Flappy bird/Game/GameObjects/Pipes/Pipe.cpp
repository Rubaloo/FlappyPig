#include "Pipe.hpp"

Pipe::Pipe(const GBox& aBody) : GObject(aBody)
{}

void Pipe::Update(double dt)
{
    kmVec3 nextPosition = mBody.Update(dt);
    kmVec3 translation = mModelView.GetTranslation();
    mBody.SetCenter(kmVec3Add(translation, mBody.GetCenter()));
    MoveBy(nextPosition);
}

void Pipe::Render() {
    
    GLMatrix projection;
    projection.PopulateOrtho(0, ASPECT_RATIO, 1, 0, -1, 1);
    
    GShader::PIPE->Enable();
    GShader::PIPE->EnableVertexAttribute("Position");
    GShader::PIPE->EnableVertexAttribute("SourceColor");
    
    kmMat4 gMatrix;
    mModelView.gMatrix(&gMatrix);
    GShader::PIPE->SetUniform4f("ModelView", gMatrix.mat);
    
    GShader::PIPE->SetUniform4f("Projection", projection.Matrix());
    mMmodelMesh.Render();
    ResetModelView();
    GShader::PIPE->Disable();
    
    
};
