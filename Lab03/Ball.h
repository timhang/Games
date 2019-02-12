#pragma once
#include "Actor.h"
#include <string>

class Ball : public Actor
{
public:
    Ball(class Game* game);
    class CollisionComponent* GetCollisionComponent();
private:
	class BallMove* bm;
    class SpriteComponent* sc;
    class CollisionComponent* cc;
};

