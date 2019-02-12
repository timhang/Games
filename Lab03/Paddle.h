#pragma once
#include "Actor.h"
#include <string>
class Paddle : public Actor
{
public:
    Paddle(class Game* game);
    void OnProcessInput(const Uint8* keyState) override;
    void OnUpdate(float deltaTime) override;
    class CollisionComponent* GetCollisionComponent();
private:
	class MoveComponent* mc;
    class SpriteComponent* sc;
    class CollisionComponent* cc;
};

