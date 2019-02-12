#pragma once
#include "Actor.h"

class Ship : public Actor
{
public:
	Ship(class Game* game);
    void OnProcessInput(const Uint8* keyState) override;
    void OnUpdate(float deltaTime) override;
private:
    class MoveComponent* mc;
    class SpriteComponent* sc;
    float interval;
};
