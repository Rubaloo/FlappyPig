#include "PipeColumn.hpp"


PipeColumn::PipeColumn(const GBox& aUpBox, const GBox& aDownBox) :
    mUp(aUpBox),
    mDown(aDownBox)
{
}

bool PipeColumn::Intersect(GObject& gObject)
{
    return (mUp.Intersect(gObject)) || (mDown.Intersect(gObject));
}

void PipeColumn::Update(float dt)
{
    mUp.Update(dt);
    mDown.Update(dt);
}

Pipe& PipeColumn::GetUp()
{
    return mUp;
}

bool PipeColumn::OutsideLeftLimits()
{
    return mUp.OutsideLeftLimits() || mDown.OutsideLeftLimits();
}

void PipeColumn::MoveTo(float xTranslation)
{
    mUp.MoveBy(kmVec3Make(xTranslation, 0, 0));
    mDown.MoveBy(kmVec3Make(xTranslation, 0, 0));
}

void PipeColumn::MoveBy(float xPosition)
{
    mUp.MoveTo(kmVec3Make(xPosition,  mUp.GetBox().GetCenter().y, 0.0));
    mDown.MoveTo(kmVec3Make(xPosition,  mDown.GetBox().GetCenter().y, 0.0));
}

void PipeColumn::Render() {
    mUp.Render();
    mDown.Render();
};

void PipeColumn::FreeModelMesh()
{
    mUp.FreeModelMesh();
    mDown.FreeModelMesh();
}
