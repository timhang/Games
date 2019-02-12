#pragma once
#include "MoveComponent.h"
#include "Math.h"

class BallMove : public MoveComponent
{
public:
    BallMove(class Actor* owner);
    void Update(float deltaTime) override;
    Vector2 GetVelocity();
    void SetVelocity(Vector2 velocity);
private:
    Vector2 velocity;

};

