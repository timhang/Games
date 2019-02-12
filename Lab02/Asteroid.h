#pragma once
#include "Actor.h"

class Asteroid : public Actor
{
public:
	Asteroid(class Game* game);
    void OnUpdate(float deltaTime) override;
    ~Asteroid();
};

