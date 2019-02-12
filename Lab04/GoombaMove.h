#pragma once
#include "MoveComponent.h"


class GoombaMove : public MoveComponent
{
public:
    GoombaMove(class Actor* owner);
    void ProcessInput(const Uint8* keyState) override;
    void Update(float deltaTime) override;
private:
    //Maybe put this in another class?
    float mYSpeed;
    bool mSpacePressed;
    bool mInAir;
};

