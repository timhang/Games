#pragma once
#include "Actor.h"
#include <string>
class Block : public Actor
{
public:
    Block(class Game* game);
    Block(class Game* game, std::string texture, int column, int row);
    ~Block();
    void ChangeTexture(std::string texture);
    class CollisionComponent* GetCollisionComponent() {
        return cc;
    }

private:
	std::string mTexture;
    class CollisionComponent* cc;
};

