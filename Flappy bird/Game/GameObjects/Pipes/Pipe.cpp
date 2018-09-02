#include "Pipe.hpp"

Pipe::Pipe(const GBox& aBody) : GObject(aBody)
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

    mModelView.populateIdentity();
    move(aBody.GetCenter());
    GLubyte modelIndexs[] = {0,1,2,3};
    mMmodelMesh = GVertexArray(modelVertexs, modelIndexs);
}

void Pipe::Update(double dt)
{
    kmVec3 nextPosition = mBody.Update(dt);
    kmVec3 translation = mModelView.getTranslation();
    mBody.SetCenter(kmVec3Add(translation, mBody.GetCenter()));
    MoveBy(nextPosition);
}

void Pipe::Render() {
    
    GLMatrix projection;
    projection.populateOrtho(0, ASPECT_RATIO, 1, 0, -1, 1);
    
    GShader::PIPE->Enable();
    GShader::PIPE->EnableVertexAttribute("Position");
    GShader::PIPE->EnableVertexAttribute("SourceColor");
    
    kmMat4 gMatrix;
    mModelView.gMatrix(&gMatrix);
    GShader::PIPE->SetUniform4f("ModelView", gMatrix.mat);
    
    GShader::PIPE->SetUniform4f("Projection", projection.matrix());
    mMmodelMesh.render();
    ResetModelView();
    GShader::PIPE->Disable();
    
    
};
