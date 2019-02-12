#pragma once
#include "Actor.h"

class Laser : public Actor
{
public:
	Laser(class Game* game);
    void OnUpdate(float deltaTime);
private:
    float lifetime = 1.0f;
};
